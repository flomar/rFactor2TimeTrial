// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <main.h>

class Application : public QApplication {
    Q_OBJECT
public:
    Application(int &_argc, char **_argv);
    virtual ~Application();
public:
    bool initialize();
    bool deinitialize();
private:
    // this variable is set at construction, as the application
    // expects that the absolute path to the configuration file
    // is passed to the executable by the user
    const QString configurationFileName;
private:
    // the following variables are all extracted after having
    // read the configuration file: the application root is the
    // folder in which the configuration file is living (this is
    // very important for locating resource files if the application
    // is executed from an arbitrary folder), and all other
    // variables are extracted from the configuration file and
    // should be more or less self-explanatory
    QString applicationRoot;
    QString applicationName;
    QString applicationVersion;
    QString applicationCopyright;
    QString applicationServerAddress;
    QString applicationServerPort;
private:
    ConfigurationFile configurationFile;
};

#endif
