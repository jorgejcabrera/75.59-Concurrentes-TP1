//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H

#include "../Image.h"

class ImageQualityFixer {
private:
    static void adjust(Image *image);

    static Image readFromFile(string file, size_t totalSize);

    static void writeInFile(string archivo, Image image);

    string fileName(string prefix, int i);

public:
    ImageQualityFixer();

    void adjustInParallel(list<Image> images);

    list<Image> adjustWithFIFO(list<Image> images);

    static Image overlap(list<Image> images);

    virtual ~ImageQualityFixer();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H
