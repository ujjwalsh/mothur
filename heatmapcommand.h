#ifndef HEATMAPCOMMAND_H
#define HEATMAPCOMMAND_H

/*
 *  heatmapcommand.h
 *  Mothur
 *
 *  Created by Sarah Westcott on 3/25/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */


#include "command.hpp"
#include "inputdata.h"
#include "readmatrix.hpp"
#include "sharedlistvector.h"


class GlobalData;


class HeatMapCommand : public Command {

public:
	HeatMapCommand();
	~HeatMapCommand();
	int execute();
	
private:
	GlobalData* globaldata;
	ReadMatrix* read;
	InputData* input;
	SharedListVector* SharedList;
	SharedOrderVector* order;
	OrderVector* ordersingle;
	string format;

};

#endif

