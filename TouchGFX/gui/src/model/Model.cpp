#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "stm32f4xx_hal.h"

extern lft_flags lftflg;

Model::Model() : modelListener(0)
{

}

void Model::tick(){
	if(lftflg.uart6_rx_flag == 1){
		modelListener->dataRxed();
		lftflg.uart6_rx_flag = 0;
	}
}
