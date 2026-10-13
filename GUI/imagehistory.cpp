#include "imagehistory.h"
#include "Image_Class.h"

void ImageHistory::setInitialState(const Image& image) {
    originalImage = image;
    hasOriginalState = true;
    clear();
}

void ImageHistory::recordState(const Image& currentImage) {
    undoStack.push(currentImage);
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

bool ImageHistory::undo(Image& currentImage) {
    if (undoStack.empty()) return false;
    redoStack.push(currentImage);
    currentImage = undoStack.top();
    undoStack.pop();
    return true;
}

bool ImageHistory::redo(Image& currentImage) {
    if (redoStack.empty()) return false;
    undoStack.push(currentImage);
    currentImage = redoStack.top();
    redoStack.pop();
    return true;
}

bool ImageHistory::reset(Image& currentImage) {
    if (!hasOriginalState) return false;

    undoStack.push(currentImage);
    while (!redoStack.empty()) redoStack.pop();

    currentImage = originalImage;
    return true;
}

void ImageHistory::clear() {
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
}