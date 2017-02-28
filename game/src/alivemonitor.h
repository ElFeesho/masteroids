#ifndef __ALIVEMONITOR_H__
#define __ALIVEMONITOR_H__

class AliveMonitor
{
public:
	virtual ~AliveMonitor()
	{
	}

    virtual bool alive() const = 0;

};

class AlwaysAlive : public AliveMonitor
{
public:
	bool alive() const;
};

#endif
