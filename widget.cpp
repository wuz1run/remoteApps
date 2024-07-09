#include "widget.h"
#include "ui_widget.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QProcess"
#include "QString"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QDebug"
#include "QInputDialog"
#include "QDir"

QString Ip;
QString UsernamE;
QString Password;
QFile file;
QString LnkInLinux;
QString ExeInLinux;
Ui_Dialog dialog;
QStringList DriveList={"A","B","C"};
QFile config("/usr/share/RemoteAPPs/config");
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 读取配置文件
    if (config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&config);
        ui->IP->setText(in.readLine());
        config.close();
    }

    readconfig();
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getIp()
{
    return ui->IP->text();
}

Ui_Dialog::~Ui_Dialog()
{
    UsernamE = Usernamer->text();
    Password = Passworder->text();
}

bool Widget::createFolder(const QString &filePath)
{
    QDir dir;
    if (!dir.exists(filePath)) {
        if (dir.mkpath(filePath)) {
            qDebug() << "Folder created successfully at" << filePath;
            return true;
        } else {
            qDebug() << "Failed to create folder at" << filePath;
            return false;
        }
    } else {
        return true;
    }
}

void Widget::on_pushButton_clicked()
{
    QString Ip = ui->IP->text();
    qDebug() << "Server opened";

    QProcess process, processer;
    QString commandtemp = "mkdir " + Widget::getDesktopPath() + "/RemoteAPPs";
    QString command2 = Widget::buildDriveCommand(Ip, "Test", UsernamE, Password);
    bool ok;

    process.start(commandtemp);
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process for mkdir";
        return;
    }
    process.waitForFinished();

    QString passwordLinux = QInputDialog::getText(nullptr, "Password", "Enter your sudo password:", QLineEdit::Password, "", &ok);
    if (!ok || passwordLinux.isEmpty()) {
        qDebug() << "Password input cancelled or empty.";
        return;
    }

    processer.start(command2);
    processer.write(passwordLinux.toUtf8() + '\n');
    processer.waitForFinished();

    QString stdOutput = processer.readAllStandardOutput();
    QString stdError = processer.readAllStandardError();
    ui->textEdit->setText(stdOutput);
    ui->textEdit->setText(stdError);
    getDrive();
}

void Widget::openedFile(const QString &File)
{
    QFileInfo fileTemp(File);
    QString extend = fileTemp.suffix();
    QString name = fileTemp.fileName();
    if (extend == "lnk") {
        handleLnk(File);
    } else if (extend == "exe") {
        handleExe(File, name);
    }
}

void Widget::handleLnk(const QString &File)
{
    QString ans = parseLink(File);
    QMessageBox::warning(this, "lnk", ans);
    QProcess::startDetached(buildCommand(Ip, ans, UsernamE, Password));
}

void Widget::handleExe(const QString &File, const QString &name)
{
    QProcess process;
    process.start("cp " + File + " " + getDesktopPath() + "/RemoteAPPs");
    process.waitForFinished();
    QString ans = getName(name);
    QProcess::startDetached(buildCommand(Ip, ans, UsernamE, Password));
}

bool Widget::isLnkFile(const QByteArray &link)
{
    return link[0x00] == 0x4C;
}

int Widget::bytes2short(const QByteArray &bytes, int off)
{
    return static_cast<unsigned char>(bytes[off]) | (static_cast<unsigned char>(bytes[off + 1]) << 8);
}

QString Widget::getNullDelimitedString(const QByteArray &bytes, int off)
{
    int len = 0;
    while (bytes[off + len] != '\0') {
        len++;
    }
    return QString::fromUtf8(bytes.mid(off, len));
}

QString Widget::parseLink(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("File not found");
    }

    QByteArray link = file.readAll();
    file.close();

    if (!isLnkFile(link)) {
        qDebug() << "Not a .lnk file";
        return "1111";
    }

    unsigned char flags = link[0x14];

    int shell_len = 0;
    if (flags & 0x1) {
        shell_len = bytes2short(link, 0x4C) + 2;
    }

    int file_start = 0x4C + shell_len;
    int local_sys_off = static_cast<unsigned char>(link[file_start + 0x10]) + file_start;

    QString real_file = getNullDelimitedString(link, local_sys_off);
    qDebug() << "Real file path:" << real_file;
    return real_file;
}

void Widget::on_TestButton_clicked()
{
    QString testLnkPath = QFileDialog::getOpenFileName(nullptr, "Choose file");
    QString ans = parseLink(testLnkPath);
    QMessageBox::warning(this, "test", ans);
    Ip = ui->IP->text();
    QString command = buildCommand(Ip, ans, UsernamE, Password);
    qDebug() << command;
    QProcess process;
    process.startDetached(command);
}

void Widget::handleDrive()
{
    QProcess process;
    QString commandtemp = "mkdir " + getDesktopPath();
    process.start(commandtemp, DriveList);
    for (const QString &s : DriveList) {
        process.start(buildDriveCommand(Ip, s, UsernamE, Password));
        process.waitForFinished();
    }
}

QString Widget::buildDriveCommand(const QString &ip, const QString &drivesymbol, const QString &username, const QString &password)
{
    QString command = QString("sudo -S mount -t cifs -o username=%1,password=%2,iocharset=utf8,dir_mode=0777,file_mode=0777,vers=3.0 //%3/%4 %5/RemoteAPPs")
                          .arg(username)
                          .arg(password)
                          .arg(ip)
                          .arg(drivesymbol)
                          .arg(getDesktopPath());
    ui->textEdit->setText(command);

    return command;
}

QString Widget::buildCommand(const QString &ip, const QString &filePath, const QString &username, const QString &password)
{
    QString command = QString("xfreerdp /v:%1 /u:%2 /p:%3 /app:\"%4\"")
                          .arg(ip)
                          .arg(username)
                          .arg(password)
                          .arg(filePath);
    qDebug() << command;
    ui->textEdit->setText(command);
    return command;
}

void Widget::rdpConnection()
{
    // To be implemented
}

void Widget::on_OpenSettings_clicked()
{
    openDialog();
}

void Widget::openDialog()
{
    QDialog *dialogue = new QDialog(this);
    readconfig();
    dialog.setupUi(dialogue);
    dialog.Usernamer->setText(UsernamE);
    dialog.Passworder->setText(Password);

    connect(dialogue, &QDialog::accepted, this, [this]() {
        UsernamE = dialog.Usernamer->text();
        Password = dialog.Passworder->text();

        QTextStream out(&config);
        Ip = ui->IP->text();
        if (config.open(QIODevice::WriteOnly | QIODevice::Text)) {
            out << Ip << endl;
            out << UsernamE << endl;
            out << Password << endl;
            config.close();
        } else {
            qDebug() << "Failed to open config file for writing";
        }
    });

    dialogue->exec();
}

void Widget::readconfig()
{
    if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open config file for reading";
        return;
    }

    QTextStream in(&config);
    if (!in.atEnd()) {
        Ip = in.readLine();
    }
    if (!in.atEnd()) {
        UsernamE = in.readLine();
    }
    if (!in.atEnd()) {
        Password = in.readLine();
    }

    config.close();

    qDebug() << "Config read:";
    qDebug() << "IP:" << Ip;
    qDebug() << "Username:" << UsernamE;
    qDebug() << "Password:" << Password;
}


QString Widget::getName(const QString &name)
{
    return "C:\\Test\\" + name;
}

void Widget::getDrive()
{
    QString drivePath=getDesktopPath()+"RemoteAPPs/config/drive.list";
    QFile drive(drivePath);
    if (!drive.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open drive file for reading";
        return;
    }

    QTextStream in(&drive);
    while(!in.atEnd())
    {
        DriveList.append(in.readLine());
    }
}

QString Widget::getDesktopPath()
{
    QProcess process;
    QString commandtemp = "xdg-user-dir";
    QStringList arguments;
    arguments << "DESKTOP";
    process.start(commandtemp, arguments);
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    ui->textEdit->setText(output);
    return output;
}


