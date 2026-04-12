#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <ctime>

extern unsigned int _id;

class Worker;
class ATool;
class Shovel;
class Hammer;


class ATool {
    public:
    ATool(const std::string& name) : _toolName(name), _numberOfUses(5U), _inUse(false) {};
    virtual ~ATool() = default;
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

    private:
        ATool() : ATool(std::string()) {};

    public:
        friend std::ostream& operator <<(std::ostream& p_os, const ATool& pTool)
        {
            p_os <<  pTool._toolName << "[" + std::to_string(pTool._numberOfUses) + "]"; 

            return (p_os);
        }
};

struct Shovel : public ATool
{
    Shovel() : ATool("Shovel") {};
    void use();
};

class Hammer : public ATool {
    public:
        Hammer() : ATool("Hammer") {};
        void use();
};

struct Position
{
    int x = 0;
    int y = 0;
    int z = 0;
};

struct Statistic
{
    int level = 1;
    int exp = 0;
};

class WorkShop;
class Worker
{
    public:
        Worker();
        Worker(const Position& pos, const Statistic& stat);
        
        ~Worker();

        void addTool(ATool* pTool);
        void releaseTool(const std::string& tool);
        void giveTool(Worker& target, const std::string& tool);

        void apply(WorkShop* Workshop);
        void work();
        inline const unsigned int getWorkerId() const {
            return (_workerId);
        }

        inline void updateEmploymentStatus(const bool status) {
            _employed = status;
        }
    private:
        ATool* getTool(const std::string& tool);
        unsigned int _workerId;
        bool _employed;
        /** Composed attributes **/
        Position    _pos;
        Statistic   _stat;

        /** Aggregated attributes **/
        std::vector<ATool*> _vTools;
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
                p_os << (pWorker._vTools[i] != nullptr ? '\t' : ' ') << *(pWorker._vTools[i]) << std::endl;
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
        void recruit(Worker* employee);
        void fire(Worker* employee);

        private:
        std::vector<Worker*> _vWorkers;
    public:
        friend std::ostream& operator <<(std::ostream& p_os, const WorkShop& pWorkShop)
        {
            p_os << std::endl << "------------WorkShop-------------" << std::endl;
            p_os << "Total Employees " << pWorkShop._vWorkers.size() << " :"<< std::endl;
            for (size_t i(0U); i < pWorkShop._vWorkers.size(); i++) {
                p_os << (pWorkShop._vWorkers[i] != nullptr ? '\t' : ' ') << "Worker " << pWorkShop._vWorkers[i]->getWorkerId() << std::endl;
            }
            p_os << "---------------------------------" << std::endl;
            return (p_os);
        }
};