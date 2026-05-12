#include "../includes/practice.hpp"

unsigned int _id = 0U;

template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value)
{
    for (; first != last; ++first) {
        if (*first == value)
            return first;
    }
    return last;
}

Worker::Worker() : _employed(false) {
    _workerId = ++_id;
    _pos.x = 0;
    _pos.y = 0;
    _pos.z = 0;
    _stat.exp = 0;
    _stat.level = 1;

    std::cout << "Worker " << static_cast<int>(_workerId) << " has joined the site !" << std::endl;
}

Worker::Worker(const Position& pos, const Statistic& stat) : _employed(false), _pos(pos), _stat(stat) {
    _workerId = ++_id;
    std::cout << "Worker " << static_cast<int>(_workerId) << " has joined the site !" << std::endl;
}

Worker::~Worker() {
    for (std::vector<Tool*>::iterator it = _vTools.begin(); it != _vTools.end(); it++) {
        if (*it) {
            (*it)->updateUsage(false);
            *it = NULL;
        }
    }
    _vTools.clear();
    std::cout << "Worker " << static_cast<int>(_workerId) << " has left the site !" << std::endl;
}

void Worker::addTool(Tool* pTool) {
    if (!pTool || pTool->isInUse())
        return ;

    this->_vTools.push_back(pTool);
    pTool->updateUsage(true);
    std::cout << "Worker "<< static_cast<int>(_workerId) << " has gained a new "<< pTool->getToolName() <<" !" << std::endl;

}

Tool* Worker::getTool(const std::string& tool) {
    for (std::vector<Tool*>::iterator it = _vTools.begin(); it != _vTools.end(); ++it) {
        if (*it && (*it)->getToolName() == tool)
            return *it;
    }
    return NULL;
}

void Worker::releaseTool(const std::string& tool) {
    Tool* pTool = getTool(tool);
    if (pTool) {
        pTool->updateUsage(false);
        std::vector<Tool*>::iterator it = find(_vTools.begin(), _vTools.end(), pTool);
        if (it != _vTools.end())
            this->_vTools.erase(it);
        std::cout << "Worker "<< static_cast<int>(_workerId) << " has released his "<< pTool->getToolName() <<" !" << std::endl;
    }
}

void Worker::giveTool(Worker& target, const std::string& tool) {
    Tool* pTool = getTool(tool);
    if (pTool) {
        releaseTool(tool);
        target.addTool(pTool);
        std::cout << "Worker "<< static_cast<int>(_workerId) << " has given his "<< pTool->getToolName() <<" to Worker " << static_cast<int>(target._workerId) << " !" << std::endl;
    } else {
        std::cout << "Worker "<< static_cast<int>(_workerId) << " does not have the tool:  " << tool << std::endl;
    }
}

void Worker::leave(WorkShop* Workshop) {
    if (Workshop) {
        std::vector<WorkShop *>::iterator it = find(_vWorkShops.begin(), _vWorkShops.end(), Workshop);
        if (it != _vWorkShops.end()) {
            _vWorkShops.erase(it);
            updateEmploymentStatus(false);
            std::cout << "Worker "<< static_cast<int>(_workerId) << " has leave his job at the Workshop !" << std::endl;
        }
    }
}

void Worker::apply(WorkShop* Workshop) {
    if (Workshop) {
        if (Workshop->recruit(this)) {
            updateEmploymentStatus(true);
            _vWorkShops.push_back(Workshop);
            std::cout << "Worker "<< static_cast<int>(_workerId) << " needs a job !" << std::endl;
        }
    }
}

bool randomBool() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        seeded = true;
    }
    return (rand() % 2) == 0;
}

void Worker::work() {
    if (!_employed)
        return ;
    std::cout << "Worker "<< static_cast<int>(_workerId) << " is working hard !" << std::endl;
    if (randomBool() == true) {
        Shovel* shovel = static_cast<Shovel*>(getTool("Shovel"));
        if (shovel)
            shovel->use();
    } else {
        Hammer* hammer = static_cast<Hammer*>(getTool("Hammer"));
        if (hammer)
            hammer->use();
    }
}

void Shovel::use() {
    std::cout << "Using Shovel" << std::endl;
    _numberOfUses--;
}

void Hammer::use() {
    std::cout << "Using Hammer" << std::endl;
    _numberOfUses--;
}

WorkShop::WorkShop() {
    std::cout << "A new WorkShop has opened" << std::endl;
}

WorkShop::WorkShop(const std::vector<Worker*>& salaryMen) : _vWorkers(salaryMen) {
    std::cout << "A new WorkShop has opened" << std::endl;
}

WorkShop::~WorkShop() {
    std::cout << "The WorkShop went bankrupt, the workers suffer massive laidoffs !" << std::endl;
    for (std::vector<Worker*>::iterator it = _vWorkers.begin(); it != _vWorkers.end(); it++)
        if (*it)
            *it = NULL;
    _vWorkers.clear();
}

void WorkShop::executeWorkDay() {
    std::cout << "Time to get to Work !" << std::endl;
    for (std::vector<Worker*>::iterator it = _vWorkers.begin(); it != _vWorkers.end(); it++)
        (*it)->work();
}

bool WorkShop::recruit(Worker* employee) {
    if (employee) {
        std::vector<Worker*>::iterator it = find(_vWorkers.begin(), _vWorkers.end(), employee);
        if (it == _vWorkers.end()) {
            _vWorkers.push_back(employee);
            employee->updateEmploymentStatus(true);
            std::cout << "Worker "<< static_cast<int>(employee->getWorkerId()) << " has join the WorkShop !" << std::endl;
            return true;
        }
    }
    return false;
}

void WorkShop::fire(Worker* employee) {
    if (employee) {
        std::vector<Worker*>::iterator it = find(_vWorkers.begin(), _vWorkers.end(), employee);
        if (it != _vWorkers.end()) {
            _vWorkers.erase(it);
            employee->updateEmploymentStatus(false);
            std::cout << "Worker "<< static_cast<int>(employee->getWorkerId()) << " has been fired from the WorkShop !" << std::endl;
        }
    }
}

void WorkShop::resignment(Worker* employee) {
    if (employee) {
        std::vector<Worker*>::iterator it = find(_vWorkers.begin(), _vWorkers.end(), employee);
        if (it != _vWorkers.end()) {
            _vWorkers.erase(it);
        }
    }
}