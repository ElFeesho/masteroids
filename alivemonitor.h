#ifndef __ALIVEMONITOR_H__
#define __ALIVEMONITOR_H__

class AliveMonitor {
public:
    virtual ~AliveMonitor() {
    }

    virtual bool alive() = 0;

};

class AlwaysAlive : public AliveMonitor {
public:
    AlwaysAlive() {
    }

    ~AlwaysAlive() {
    }

    bool alive() {
        return true;
    }

    static AlwaysAlive alivemonitor;
};

#endif
