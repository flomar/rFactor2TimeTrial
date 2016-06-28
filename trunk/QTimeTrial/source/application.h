// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <main.h>

#define APPLICATION_NAME "QTimeTrial"
#define APPLICATION_COPYRIGHT "(C) 2016 flomar"

class Application : public QApplication {
    Q_OBJECT
public:
    Application(int &_argc, char **_argv);
    virtual ~Application();
public:
    bool initialize();
    bool deinitialize();
};

#endif
