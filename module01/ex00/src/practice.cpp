#include "../includes/practice.hpp"

unsigned int _id = 0U;

Worker::Worker() : _pos{0,0,0}, _stat{1, 0} {
    _workerId = ++_id;
    std::cout << "Worker " << static_cast<int>(_workerId) << " has joined the site !" << std::endl;
}

Worker::Worker(const Position& pos, const Statistic& stat) : _pos(pos), _stat(stat) {
    _workerId = ++_id;
    std::cout << "Worker " << static_cast<int>(_workerId) << " has joined the site !" << std::endl;
}

Worker::~Worker() {
    for (std::vector<ATool*>::iterator it = _vTools.begin(); it != _vTools.end(); it++) {
        if (*it) {
            (*it)->updateUsage(false);
            *it = nullptr;
        }
    }
    _vTools.clear();
    std::cout << "Worker " << static_cast<int>(_workerId) << " has left the site !" << std::endl;
}

void Worker::addTool(ATool* pTool) {
    if ((pTool) && (!pTool->isInUse())) {
        this->_vTools.push_back(pTool);
        pTool->updateUsage(true);
        std::cout << "Worker "<< static_cast<int>(_workerId) << " has gained a new "<< pTool->getToolName() <<" !" << std::endl;
    }
}

ATool* Worker::getTool(const std::string& tool) {
    std::vector<ATool*>::iterator it = std::find_if(_vTools.begin(), _vTools.end(),
                                                    [&tool](ATool* item) { return (item && item->getToolName() == "Shovel");});
    return ((it != _vTools.end()) ? *it : nullptr);
}

void Worker::releaseTool(const std::string& tool) {
    ATool* pTool = getTool(tool);
    if (pTool) {
        pTool->updateUsage(false);
        this->_vTools.erase(std::find(_vTools.begin(), _vTools.end(), pTool));
    }
    std::cout << "Worker "<< static_cast<int>(_workerId) << " has released his "<< pTool->getToolName() <<" !" << std::endl;
}

void Worker::giveTool(Worker& target, const std::string& tool) {
    ATool* pTool = getTool(tool);
    if (pTool) {
        releaseTool(tool);
        target.addTool(pTool);
    }

    std::cout << "Worker "<< static_cast<int>(_workerId) << " has given his "<< pTool->getToolName() <<" to Worker " << static_cast<int>(target._workerId) << " !" << std::endl;
}



void Worker::apply(WorkShop* Workshop) {
    if (Workshop) {
        std::cout << "Worker "<< static_cast<int>(_workerId) << " needs a job !" << std::endl;
        Workshop->recruit(this);
        _employed = true;
    }
}

bool randomBool() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        seeded = true;
    }
    std::cout << (rand() % 2) << std::endl; 
    return (rand() % 2) == 0;
}
void Worker::work() {
    if (!_employed)
        return ;
    std::cout << "Worker "<< static_cast<int>(_workerId) << " is working hard !" << std::endl;
    if (randomBool() == true) {
        std::cout << "oiasdufgbuoisadbgfoaisujbdaiousdbasiodubasoidubhasdoiugbasoiujdbasujoibdujaiosbd" << std::endl;
        Shovel* shovel = static_cast<Shovel*>(getTool("Shovel"));
        if (shovel)(rand() % 2)
            shovel->use();
    } else {
        std::cout << "putain de marteau" << std::endl;
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
            *it = nullptr;
    _vWorkers.clear();
}

void WorkShop::executeWorkDay() {
    std::cout << "Time to get to Work !" << std::endl;
    for (std::vector<Worker*>::iterator it = _vWorkers.begin(); it != _vWorkers.end(); it++)
        (*it)->work();
}

void WorkShop::recruit(Worker* employee) {
    if (employee) {
        this->_vWorkers.push_back(employee);
        employee->updateEmploymentStatus(true);
        std::cout << "Worker "<< static_cast<int>(employee->getWorkerId()) << " has join the WorkShop !" << std::endl;
    }
}

void WorkShop::fire(Worker* employee) {
    if (employee) {
        std::vector<Worker*>::iterator it = std::find(_vWorkers.begin(), _vWorkers.end(), employee);
        if (it != _vWorkers.end()) {
            _vWorkers.erase(it);
            employee->updateEmploymentStatus(false);
            std::cout << "Worker "<< static_cast<int>(employee->getWorkerId()) << " has been fired from the WorkShop !" << std::endl;
        }
    }
}