#ifndef IMAGEHISTORY_H
#define IMAGEHISTORY_H

#include <stack>
#include "Image_Class.h"

class ImageHistory {
private:
    Image originalImage;
    bool hasOriginalState = false;

    std::stack<Image> undoStack;
    std::stack<Image> redoStack;

public:
    ImageHistory() = default;

    void setInitialState(const Image& image);
    void recordState(const Image& currentImage);
    bool undo(Image& currentImage);
    bool redo(Image& currentImage);
    bool reset(Image& currentImage);
    void clear();
};

#endif