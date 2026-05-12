#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <sstream>

extern unsigned int _id;

class Worker;
class Tool;
class Shovel;
class Hammer;


class Tool {
    public:
    Tool(const std::string& name) : _toolName(name), _numberOfUses(5U), _inUse(false) {};
    virtual ~Tool() {};
    virtual void use() = 0;
    
    bool isInUse() {
        return (_inUse);
    }
    void updateUsage(const bool usage) {
        _inUse = usage;
    }
    const std::string getToolName() const {
        return (_toolName);
    }
    protected:
        std::string _toolName;
        unsigned int _numberOfUses;
        bool _inUse;

    public:
        friend std::ostream& operator <<(std::ostream& p_os, const Tool& pTool)
        {
            std::ostringstream oss;
            oss << pTool._numberOfUses;
            p_os <<  pTool._toolName << "[" +  oss.str() + "]"; 

            return (p_os);
        }
};

struct Shovel : public Tool
{
    Shovel() : Tool("Shovel") {};
    void use();
};

class Hammer : public Tool {
    public:
        Hammer() : Tool("Hammer") {};
        void use();
};

struct Position
{
    int x;
    int y;
    int z;
};

struct Statistic
{
    int level;
    int exp;
};

class WorkShop;
class Worker
{
    public:
        Worker();
        Worker(const Position& pos, const Statistic& stat);
        
        ~Worker();

        void addTool(Tool* pTool);
        void releaseTool(const std::string& tool);
        void giveTool(Worker& target, const std::string& tool);

        void apply(WorkShop* Workshop);
        void leave(WorkShop* Workshop);
        void work();
        inline unsigned int getWorkerId() const {
            return (_workerId);
        }

        inline void updateEmploymentStatus(const bool status) {
            if ((status == false) && (_vWorkShops.empty())) {
                _employed = false;
                return ;
            }
            _employed = status;
        }
    private:
        Tool* getTool(const std::string& tool);
        unsigned int _workerId;
        bool _employed;
        /** Composed attributes **/
        Position    _pos;
        Statistic   _stat;

        /** Aggregated attributes **/
        std::vector<Tool*> _vTools;
        /** Association attributes **/
        std::vector<WorkShop*> _vWorkShops;

    public:
        friend std::ostream& operator <<(std::ostream& p_os, const Worker& pWorker)
        {
            p_os << std::endl << "-------------------------" << std::endl;
            p_os << "Worker["<< static_cast<int>(pWorker._workerId) <<"]: {" << pWorker._pos.x << ';' << pWorker._pos.y << ';' << pWorker._pos.z << '}' << std::endl;
            p_os << "Level ["<< pWorker._stat.level << "] | exp: " << pWorker._stat.exp << std::endl;
            p_os << "Items :"<< std::endl;
            for (size_t i(0U); i < pWorker._vTools.size(); i++) {
                p_os << (pWorker._vTools[i] != NULL ? '\t' : ' ') << *(pWorker._vTools[i]) << std::endl;
            }
            p_os << "-------------------------" << std::endl;
            return (p_os);
        }
};

class WorkShop {
    public:
        WorkShop();
        WorkShop(const std::vector<Worker*>& salaryMen);
        virtual ~WorkShop();

        void executeWorkDay();
        bool recruit(Worker* employee);
        void fire(Worker* employee);
        void resignment(Worker* employee);

    private:
        std::vector<Worker*> _vWorkers;
    public:
        friend std::ostream& operator <<(std::ostream& p_os, const WorkShop& pWorkShop)
        {
            p_os << std::endl << "------------WorkShop-------------" << std::endl;
            p_os << "Total Employees " << pWorkShop._vWorkers.size() << " :"<< std::endl;
            for (size_t i(0U); i < pWorkShop._vWorkers.size(); i++) {
                p_os << (pWorkShop._vWorkers[i] != NULL ? '\t' : ' ') << "Worker " << pWorkShop._vWorkers[i]->getWorkerId() << std::endl;
            }
            p_os << "---------------------------------" << std::endl;
            return (p_os);
        }
};
