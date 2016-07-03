// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <main.h>

#include <applicationdatabase.h>
#include <applicationserver.h>
#include <applicationgui.h>

#include <utilities.h>

class Application : public QApplication {
    Q_OBJECT
public:
    Application(int &_argc, char **_argv);
    virtual ~Application();
public:
    bool initialize();
    bool deinitialize();
private:
    QQmlApplicationEngine *qmlApplicationEngine;
private:
    ApplicationDatabase *applicationDatabase;
    ApplicationServer *applicationServer;
    ApplicationGui *applicationGui;
public:
    ApplicationDatabase *getApplicationDatabase() { return applicationDatabase; }
    ApplicationServer *getApplicationServer() { return applicationServer; }
    ApplicationGui *getApplicationGui() { return applicationGui; }
public:
    const ApplicationDatabase *getApplicationDatabaseConst() const { return applicationDatabase; }
    const ApplicationServer *getApplicationServerConst() const { return applicationServer; }
    const ApplicationGui *getApplicationGuiConst() const { return applicationGui; }
private:
    // this variable is set at construction, as the application
    // expects that the absolute path to the configuration file
    // is passed to the executable by the user
    const QString configurationFileName;
    // this function parses the configuration file; it is called
    // during initialization and returns false if not all variables
    // can be properly extracted
    bool parseConfigurationFile(const QString &_configurationFileName);
private:
    // the following variables are all extracted through parsing
    // the configuration file: the application root is the folder
    // in which the configuration file is living (this is very
    // important for locating resource files if the application
    // is executed from an arbitrary folder), and all other
    // variables are extracted from the configuration file and
    // should be more or less self-explanatory
    QString applicationRoot;
    QString applicationName;
    QString applicationVersion;
    QString applicationCopyright;
    QString applicationDatabaseFileName;
    QString applicationServerAddress;
    QString applicationServerPort;
public:
    // this function creates an absolute file path out of the
    // specified relative file path by prepending the application
    // root folder (as initialized through the configuration file)
    QString getAbsoluteFilePath(const QString &_relativeFilePath) const;
};

#endif
