#include "directorychangedthread.h"
#include <syslog.h>
#include <QIcon>

DirectoryChangedThread::DirectoryChangedThread()
{
    pUkuiMenuInterface=new UkuiMenuInterface;
    QString path=QDir::homePath()+"/.config/ukui/ukui-menu.ini";
    setting=new QSettings(path,QSettings::IniFormat);

}

DirectoryChangedThread::~DirectoryChangedThread()
{
    delete pUkuiMenuInterface;
}

void DirectoryChangedThread::run()
{
    if(this->path=="/usr/share/applications")
    {
        QStringList desktopfpList=pUkuiMenuInterface->getDesktopFilePath();
        if(desktopfpList.size() > UkuiMenuInterface::desktopfpVector.size())//有新的应用安装
        {
            syslog(LOG_LOCAL0 | LOG_DEBUG ,"---111---");
//            sleep(10);
            syslog(LOG_LOCAL0 | LOG_DEBUG ,"---222---");
            setting->beginGroup("recentapp");
            for(int i=0;i<desktopfpList.count();i++)
            {
                if(!UkuiMenuInterface::desktopfpVector.contains(desktopfpList.at(i)))
                {
                    //获取当前时间戳
                    QDateTime dt=QDateTime::currentDateTime();
                    int datetime=dt.toTime_t();
                    QFileInfo fileInfo(desktopfpList.at(i));
                    QString desktopfn=fileInfo.fileName();
                    setting->setValue(desktopfn,datetime);

                    QString iconstr=pUkuiMenuInterface->getAppIcon(desktopfpList.at(i));
                    syslog(LOG_LOCAL0 | LOG_DEBUG ,"%s",iconstr.toLocal8Bit().data());
                    syslog(LOG_LOCAL0 | LOG_DEBUG ,"软件安装desktop文件名：%s",desktopfn.toLocal8Bit().data());
                    Q_FOREACH(QString path,QIcon::themeSearchPaths())
                        syslog(LOG_LOCAL0 | LOG_DEBUG ,"%s",path.toLocal8Bit().data());
                    break;
                }

            }
            setting->endGroup();
            UkuiMenuInterface::appInfoVector.clear();
            UkuiMenuInterface::alphabeticVector.clear();
            UkuiMenuInterface::functionalVector.clear();
            UkuiMenuInterface::appInfoVector=pUkuiMenuInterface->createAppInfoVector();
            UkuiMenuInterface::alphabeticVector=pUkuiMenuInterface->getAlphabeticClassification();
            UkuiMenuInterface::functionalVector=pUkuiMenuInterface->getFunctionalClassification();
            Q_EMIT requestUpdateSignal();
        }
        else//软件卸载
        {
            for(int i=0;i<UkuiMenuInterface::desktopfpVector.size();i++)
            {
                if(!desktopfpList.contains(UkuiMenuInterface::desktopfpVector.at(i)))
                {
                    QString desktopfp=UkuiMenuInterface::appInfoVector.at(i).at(0);
                    QFileInfo fileInfo(desktopfp);
                    QString desktopfn=fileInfo.fileName();
                    setting->beginGroup("lockapplication");
                    setting->remove(desktopfn);
                    setting->sync();
                    setting->endGroup();
                    setting->beginGroup("application");
                    setting->remove(desktopfn);
                    setting->sync();
                    setting->endGroup();
                    setting->beginGroup("datetime");
                    setting->remove(desktopfn);
                    setting->sync();
                    setting->endGroup();
                    setting->beginGroup("recentapp");
                    setting->remove(desktopfn);
                    setting->sync();
                    setting->endGroup();
                    syslog(LOG_LOCAL0 | LOG_DEBUG ,"软件卸载desktop文件名：%s",desktopfn.toLocal8Bit().data());
                    break;
                }
            }
            UkuiMenuInterface::appInfoVector.clear();
            UkuiMenuInterface::alphabeticVector.clear();
            UkuiMenuInterface::functionalVector.clear();
            UkuiMenuInterface::appInfoVector=pUkuiMenuInterface->createAppInfoVector();
            UkuiMenuInterface::alphabeticVector=pUkuiMenuInterface->getAlphabeticClassification();
            UkuiMenuInterface::functionalVector=pUkuiMenuInterface->getFunctionalClassification();
            Q_EMIT requestUpdateSignal();
        }
    }
}

void DirectoryChangedThread::recvDirectoryPath(QString arg)
{
    this->path.clear();
    this->path=arg;
}
