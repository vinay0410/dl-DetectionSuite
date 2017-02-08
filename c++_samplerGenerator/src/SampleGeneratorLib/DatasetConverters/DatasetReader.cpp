//
// Created by frivas on 22/01/17.
//

#include <unordered_map>
#include "DatasetReader.h"
#include "ClassTypeOwn.h"


DatasetReader::DatasetReader():readerCounter(0) {
}

void DatasetReader::filterSamplesByID(std::vector<std::string> filteredIDS) {
    std::vector<Sample> old_samples(this->samples);
    this->samples.clear();

    for (auto it=old_samples.begin(), end=old_samples.end(); it != end; ++it){
        Sample& sample =*it;
        sample.filterSamplesByID(filteredIDS);
        if (sample.getContourRegions() && sample.getContourRegions()->empty() && sample.getRectRegions()->empty()){

        }
        else{
            this->samples.push_back(sample);
        }
    }
}

int DatasetReader::getNumberOfElements() {
    return this->samples.size();
}

void DatasetReader::resetReaderCounter() {
    this->readerCounter=0;

}

bool DatasetReader::getNetxSample(Sample &sample) {
    std::cout << "readCounter: " << this->readerCounter << ", size: " << this->samples.size() << std::endl;
    if (this->readerCounter < this->samples.size()){
        sample=this->samples[this->readerCounter];
        this->readerCounter++;
        return true;
    }
    else{
        return false;
    }

}



bool DatasetReader::getSampleBySampleID(Sample** sample, const std::string& sampleID){
    for (auto it=this->samples.begin(), end= this->samples.end(); it != end; ++it){
        if (it->getSampleID().compare(sampleID)==0){
            *sample=&(*it);
            return true;
        }
    }
    return false;
}

void DatasetReader::printDatasetStats() {
    std::unordered_map<int, int> classStats;

    for (auto it=samples.begin(), end=samples.end(); it != end; ++it){
        RectRegionsPtr regions = it->getRectRegions();
        std::vector<RectRegion> regionsVector = regions->getRegions();
        for (std::vector<RectRegion>::iterator itRegion= regionsVector.begin(), endRegion =regionsVector.end(); itRegion != endRegion; ++itRegion){
            std::string test = itRegion->classID;
            ClassTypeOwn typeconv(test);
            if (classStats.count(typeconv.getClassID())){
                classStats[typeconv.getClassID()]++;
            }
            else{
                classStats.insert(std::make_pair(typeconv.getClassID(),1));
            }
        }
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    for (auto it = classStats.begin(), end = classStats.end(); it != end; ++it){
        ClassTypeOwn typeconv(it->first);

        std::cout << "["<< typeconv.getClassString() <<  "]: " << it->second << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "------------------------------------------" << std::endl;


}

void DatasetReader::addSample(Sample sample) {
    this->samples.push_back(sample);
}

bool DatasetReader::appendDataset(const std::string &datasetPath, const std::string &datasetPrefix) {
    return false;
}

