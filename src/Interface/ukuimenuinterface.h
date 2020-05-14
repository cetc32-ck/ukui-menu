/*
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#ifndef UKUIMENUINTERFACE_H
#define UKUIMENUINTERFACE_H
#include <QtCore>
#include <sys/types.h>
#include <unistd.h>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusObjectPath>
#include <QSettings>

class UkuiMenuInterface
{
private:
    QStringList filePathList;
    QSettings* setting=nullptr;

protected:
    void recursiveSearchFile(const QString& _filePath);//遍历/usr/share/applications/文件夹
    QStringList getSpecifiedCategoryAppList(QString categorystr);//获取指定类型应用列表

public:
    UkuiMenuInterface();
    ~UkuiMenuInterface();
    QVector<QStringList> createAppInfoVector();//创建应用信息容器
    static QVector<QStringList> appInfoVector;
    static QVector<QString> desktopfpVector;
    static QVector<QStringList> alphabeticVector;
    static QVector<QStringList> functionalVector;
    static QVector<QString> allAppVector;

    /**
     * 获取系统应用名称
     * @param desktopfp 为应用.desktop文件所在路径
     * @return 返回应用名称
     */
    QString getAppName(QString desktopfp);//获取应用名
    QString getAppEnglishName(QString desktopfp);//获取英语英文名
    QString getAppIcon(QString desktopfp);//获取应用图像
    QString getAppCategories(QString desktopfp);//获取应用分类
    QString getAppExec(QString desktopfp);//获取应用命令
    QString getAppType(QString desktopfp);//获取应用类型
    QString getAppComment(QString desktopfp);//获取应用注释

    QStringList getDesktopFilePath();//获取系统deskyop文件路径

    QString getDesktopPathByAppName(QString appname);//根据应用名获取deskyop文件路径
    QString getDesktopPathByCommand(QString command);//根据命令获取deskyop文件路径
    QString getDesktopPathByAppEnglishName(QString appname);//根据应用英文名获取deskyop文件路径

    QVector<QStringList> getAlphabeticClassification();//获取字母分类
    QVector<QStringList> getFunctionalClassification();//获取功能分类
    QVector<QString> getCommonUseApp();//获取常用App
    QVector<QString> getAllApp();
    QStringList getRecentApp();//获取最近添加App
    QStringList getAndroidApp();//获取安卓应用
    bool matchingAppCategories(QString desktopfp,QStringList categorylist);//匹配应用Categories

    QString getAppNamePinyin(QString appname);//获取应用名拼音

    //获取用户图像
    QString getUserIcon();
    //获取用户姓名
    QString getUserName();

};

#endif // UKUIMENUINTERFACE_H
