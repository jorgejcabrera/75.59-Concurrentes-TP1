//
// Created by Jorge Cabrera on 17/11/2020.
//

#include "ImageService.h"

size_t ImageService::serializedSize(list<Image> images) {
    return images.size() * images.begin()->getSerializedSize();
}