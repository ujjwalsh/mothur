/*
 *  collectsharedcommand.cpp
 *  Dotur
 *
 *  Created by Sarah Westcott on 1/2/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "collectsharedcommand.h"
#include "sharedsobscollectsummary.h"
#include "sharedchao1.h"
#include "sharedace.h"
#include "sharedjabund.h"
#include "sharedsorabund.h"
#include "sharedjclass.h"
#include "sharedsorclass.h"
#include "sharedjest.h"
#include "sharedsorest.h"
#include "sharedthetayc.h"
#include "sharedthetan.h"
#include "sharedkstest.h"
#include "sharedbdiversity.h"
#include "sharednseqs.h"
#include "sharedochiai.h"
//#include "sharedanderberg.h"
#include "sharedkulczynski.h"
#include "sharedkulczynskicody.h"
#include "sharedlennon.h"
#include "sharedmorisitahorn.h"
#include "sharedbraycurtis.h"



//**********************************************************************************************************************

CollectSharedCommand::CollectSharedCommand(){
	try {
		globaldata = GlobalData::getInstance();
		string fileNameRoot;
		fileNameRoot = getRootName(globaldata->inputFileName);
		format = globaldata->getFormat();
		validCalculator = new ValidCalculators();
		
		int i;
		for (i=0; i<globaldata->Estimators.size(); i++) {
			if (validCalculator->isValidCalculator("shared", globaldata->Estimators[i]) == true) { 
				if (globaldata->Estimators[i] == "sharedchao") { 
					cDisplays.push_back(new CollectDisplay(new SharedChao1(), new SharedOneColumnFile(fileNameRoot+"shared.chao")));
				}else if (globaldata->Estimators[i] == "sharedsobs") { 
					cDisplays.push_back(new CollectDisplay(new SharedSobsCS(), new SharedOneColumnFile(fileNameRoot+"shared.sobs")));
				}else if (globaldata->Estimators[i] == "sharedace") { 
					cDisplays.push_back(new CollectDisplay(new SharedAce(), new SharedOneColumnFile(fileNameRoot+"shared.ace")));
				}else if (globaldata->Estimators[i] == "sharedjabund") { 	
					cDisplays.push_back(new CollectDisplay(new SharedJAbund(), new SharedOneColumnFile(fileNameRoot+"shared.jabund")));
				}else if (globaldata->Estimators[i] == "sharedsorensonabund") { 
					cDisplays.push_back(new CollectDisplay(new SharedSorAbund(), new SharedOneColumnFile(fileNameRoot+"shared.sorabund")));
				}else if (globaldata->Estimators[i] == "sharedjclass") { 
					cDisplays.push_back(new CollectDisplay(new SharedJclass(), new SharedOneColumnFile(fileNameRoot+"shared.jclass")));
				}else if (globaldata->Estimators[i] == "sharedsorclass") { 
					cDisplays.push_back(new CollectDisplay(new SharedSorClass(), new SharedOneColumnFile(fileNameRoot+"shared.sorclass")));
				}else if (globaldata->Estimators[i] == "sharedjest") { 
					cDisplays.push_back(new CollectDisplay(new SharedJest(), new SharedOneColumnFile(fileNameRoot+"shared.jest")));
				}else if (globaldata->Estimators[i] == "sharedsorest") { 
					cDisplays.push_back(new CollectDisplay(new SharedSorEst(), new SharedOneColumnFile(fileNameRoot+"shared.sorest")));
				}else if (globaldata->Estimators[i] == "sharedthetayc") { 
					cDisplays.push_back(new CollectDisplay(new SharedThetaYC(), new SharedOneColumnFile(fileNameRoot+"shared.thetayc")));
				}else if (globaldata->Estimators[i] == "sharedthetan") { 
					cDisplays.push_back(new CollectDisplay(new SharedThetaN(), new SharedOneColumnFile(fileNameRoot+"shared.thetan")));
				}else if (globaldata->Estimators[i] == "sharedkstest") { 
					cDisplays.push_back(new CollectDisplay(new SharedKSTest(), new SharedOneColumnFile(fileNameRoot+"shared.kstest")));
				}else if (globaldata->Estimators[i] == "sharedbdiversity") { 
					cDisplays.push_back(new CollectDisplay(new SharedBDiversity(), new SharedOneColumnFile(fileNameRoot+"shared.bdiversity")));
				}else if (globaldata->Estimators[i] == "sharednseqs") { 
					cDisplays.push_back(new CollectDisplay(new SharedNSeqs(), new SharedOneColumnFile(fileNameRoot+"shared.nseqs")));
				}else if (globaldata->Estimators[i] == "sharedochiai") { 
					cDisplays.push_back(new CollectDisplay(new SharedOchiai(), new SharedOneColumnFile(fileNameRoot+"shared.ochiai")));
				//}else if (globaldata->Estimators[i] == "sharedanderberg") { 
				//	cDisplays.push_back(new CollectDisplay(new SharedAnderberg(), new SharedOneColumnFile(fileNameRoot+"shared.anderberg")));
				}else if (globaldata->Estimators[i] == "sharedkulczynski") { 
					cDisplays.push_back(new CollectDisplay(new SharedKulczynski(), new SharedOneColumnFile(fileNameRoot+"shared.kulczynski")));
				}else if (globaldata->Estimators[i] == "sharedkulczynskicody") { 
					cDisplays.push_back(new CollectDisplay(new SharedKulczynskiCody(), new SharedOneColumnFile(fileNameRoot+"shared.kulczynskicody")));
				}else if (globaldata->Estimators[i] == "sharedlennon") { 
					cDisplays.push_back(new CollectDisplay(new SharedLennon(), new SharedOneColumnFile(fileNameRoot+"shared.lennon")));
				}else if (globaldata->Estimators[i] == "sharedmorisitahorn") { 
					cDisplays.push_back(new CollectDisplay(new SharedMorHorn(), new SharedOneColumnFile(fileNameRoot+"shared.morisitahorn")));
				}else if (globaldata->Estimators[i] == "sharedbraycurtis") { 
					cDisplays.push_back(new CollectDisplay(new SharedBrayCurtis(), new SharedOneColumnFile(fileNameRoot+"shared.braycurtis")));
				}
			}
		}
		
		//reset calc for next command
		globaldata->setCalc("");

	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the CollectSharedCommand class Function CollectSharedCommand. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the CollectSharedCommand class function CollectSharedCommand. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}	
			
}

//**********************************************************************************************************************

CollectSharedCommand::~CollectSharedCommand(){
	delete order;
	delete input;
	delete cCurve;
	delete read;
}

//**********************************************************************************************************************

int CollectSharedCommand::execute(){
	try {
		int count = 1;
		
		//if the users entered no valid calculators don't execute command
		if (cDisplays.size() == 0) { return 0; }
		
		if (format == "sharedfile") {
			read = new ReadPhilFile(globaldata->inputFileName);	
			read->read(&*globaldata); 
			
			input = globaldata->ginput;
			order = input->getSharedOrderVector();
		}else {
			//you are using a list and a groupfile
			read = new ReadPhilFile(globaldata->inputFileName);	
			read->read(&*globaldata); 
		
			input = globaldata->ginput;
			SharedList = globaldata->gSharedList;
			order = SharedList->getSharedOrderVector();
		}
		set<string> orderList;
		
		//set users groups
		setGroups();

		while(order != NULL){
			orderList.insert(order->getLabel());
			if(globaldata->allLines == 1 || globaldata->lines.count(count) == 1 || globaldata->labels.count(order->getLabel()) == 1){
				//create collectors curve
				cCurve = new Collect(order, cDisplays);
				convert(globaldata->getFreq(), freq);
				cCurve->getSharedCurve(freq);
			
				delete cCurve;
			
				cout << order->getLabel() << '\t' << count << endl;
			}
			
			//get next line to process
			if (format == "sharedfile") {
				order = input->getSharedOrderVector();
			}else {
				//you are using a list and a groupfile
				SharedList = input->getSharedListVector(); //get new list vector to process
				if (SharedList != NULL) {
					order = SharedList->getSharedOrderVector(); //gets new order vector with group info.
				}else {
					break;
				}
			}
			
			count++;
		}
		set<string>::iterator i;
		for(i = globaldata->labels.begin(); i != globaldata->labels.end(); ++i)
			if(orderList.count(*i) == 0)
				cout << "'" << *i << "'" << " is not a valid label.\n";
		for(int i=0;i<cDisplays.size();i++){	delete cDisplays[i];	}	
		
		//reset groups parameter
		globaldata->Groups.clear();  globaldata->setGroups("");
		
		return 0;
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the CollectSharedCommand class Function execute. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the CollectSharedCommand class function execute. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}	
}


//**********************************************************************************************************************
void CollectSharedCommand::setGroups() {
	try {
		//if the user has not entered specific groups to analyze then do them all
		if (globaldata->Groups.size() != 0) {
			if (globaldata->Groups[0] != "all") {
				//check that groups are valid
				for (int i = 0; i < globaldata->Groups.size(); i++) {
					if (globaldata->gGroupmap->isValidGroup(globaldata->Groups[i]) != true) {
						cout << globaldata->Groups[i] << " is not a valid group, and will be disregarded." << endl;
						// erase the invalid group from globaldata->Groups
						globaldata->Groups.erase(globaldata->Groups.begin()+i);
					}
				}
			
				//if the user only entered invalid groups
				if ((globaldata->Groups.size() == 0) || (globaldata->Groups.size() == 1)) { 
					cout << "When using the groups parameter you must have at least 2 valid groups. I will run the command using all the groups in your groupfile." << endl; 
					for (int i = 0; i < globaldata->gGroupmap->namesOfGroups.size(); i++) {
						globaldata->Groups.push_back(globaldata->gGroupmap->namesOfGroups[i]);
					}
				}
			}else{//user has enter "all" and wants the default groups
				globaldata->Groups.clear();
				for (int i = 0; i < globaldata->gGroupmap->namesOfGroups.size(); i++) {
					globaldata->Groups.push_back(globaldata->gGroupmap->namesOfGroups[i]);
				}
				globaldata->setGroups("");
			}
		}else {
			for (int i = 0; i < globaldata->gGroupmap->namesOfGroups.size(); i++) {
				globaldata->Groups.push_back(globaldata->gGroupmap->namesOfGroups[i]);
			}
		}
		
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the CollectSharedCommand class Function setGroups. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the CollectSharedCommand class function setGroups. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}		

}
/***********************************************************/

