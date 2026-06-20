#pragma once

#include "pch.h"
#include "Store.h"
#include "Report.h"

int showMenu();
string randomStoreName(int i);
string randomPersonName();
double randomDouble(double min, double max);
int randomInt(int min, int max);

Store generateOneStore(int index);
Store* generateStores(int count);
void saveAllStores(const string& filename, Store* stores, int count);
Store* loadAllStores(const string& filename, int& count);
void showRankingReport(Store* stores, int count);
void showProfitThenGrowthReport(Store* stores, int count);
