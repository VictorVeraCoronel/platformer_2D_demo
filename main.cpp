#include <iostream>
#include <memory>
#include "./core/world.h"

int main(){

    std::unique_ptr<World> world = std::make_unique<World>();

    std::cout<<"TEST"<<std::endl;

    return 0;
}
