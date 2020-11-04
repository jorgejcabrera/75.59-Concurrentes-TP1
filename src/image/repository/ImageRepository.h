//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H

#include "../Image.h"

class ImageRepository {
private:
    size_t sizeOfElement{};

    static string partitionKey(int i);

public:
    ImageRepository();

    explicit ImageRepository(size_t sizeOfElement);

    static void saveAll(list<Image> images, int *ptr);

    void saveInPosition(const Image &image, int position, int *ptr) const;

    Image findByPosition(int position, int *ptr) const;

    list<Image> findAll(int totalImages, int *ptr) const;

    static Image findByPartition(int partition, size_t totalSize);

    static void saveToPartition(int partition, Image image);

    virtual ~ImageRepository();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
