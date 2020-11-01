//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H

#include "../Image.h"

class ImageRepository {
private:
    size_t sizeOfElement{};

    static void save(Image image, int *ptr);

    static Image read(const int *ptr);

public:
    ImageRepository();

    explicit ImageRepository(size_t sizeOfElement);

    void saveAll(list<Image> images, int *ptr);

    void saveAtPosition(const Image &image, int position, int *ptr);

    Image findByPosition(int position, int *ptr);

    list<Image> findAll(int totalImages, int *ptr);

    virtual ~ImageRepository();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
