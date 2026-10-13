#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Image_Class.h"
#include "stb_image.h"
#include "Image_Class.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include "Filter_Parameters.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QShortcut>
#include <QRadioButton>
// #include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setAcceptDrops(false);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragOnly);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);
    ui->dropContainerWidget->setAcceptDrops(true);

    ui->imageLabel->setAcceptDrops(true);
    ui->imageLabel->viewport()->setAcceptDrops(true);
    ui->imageLabel->viewport()->installEventFilter(this);    this->setAcceptDrops(true);
    ui->imageLabel->installEventFilter(this);
    QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);

    QShortcut *shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(shortcutUndo, &QShortcut::activated, this, &MainWindow::on_btnUndo_clicked);

    QShortcut *shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(shortcutRedo, &QShortcut::activated, this, &MainWindow::on_btnRedo_clicked);

    QShortcut *shortcutSave = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(shortcutSave, &QShortcut::activated, this, &MainWindow::on_btnSave_clicked);

    QShortcut *shortcutOpen = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(shortcutOpen, &QShortcut::activated, this, &MainWindow::on_btnOpen_clicked);
    scene = new QGraphicsScene(this);
    ui->imageLabel->setScene(scene);

    ui->imageLabel->setDragMode(QGraphicsView::ScrollHandDrag);

    ui->imageLabel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->imageLabel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->redvalue, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::on_redvalue_valueChanged);
    ui->sidebarFrame->setMaximumWidth(220);
    ui->sidebarFrame->setMinimumWidth(0);
    this->setWindowTitle("AURAPIXEL");

    if (ui->centralwidget->layout()) {
        QBoxLayout *mainLayout = qobject_cast<QBoxLayout*>(ui->centralwidget->layout());
        if (mainLayout) {
            mainLayout->setStretch(0, 0);
            mainLayout->setStretch(1, 1);
            mainLayout->setStretch(2, 0);
        }
    }
    on_btnApplydarkTheme_clicked();
    ui->imageLabel->setAcceptDrops(true);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMouseTracking(true);
    ui->imageLabel->setMouseTracking(true);
    ui->frameContainer->hide();
    ui->lightenDarkenSlider->setRange(-100, 100);
    ui->lightenDarkenSlider->setValue(0);


    connect(ui->lightenDarkenSlider, &QSlider::valueChanged, ui->lightenDarkenSpinBox, &QSpinBox::setValue);
    // connect(ui->lightenDarkenSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->lightenDarkenSlider, &QSlider::setValue);

    // connect(ui->lightenDarkenSlider, &QSlider::valueChanged, this, &MainWindow::on_lightenDarkenSlider_valueChanged);
    ui->cropRotateContainer->setVisible(false);
    ui->RGB_widget->setVisible(false);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setIconSize(QSize(80, 80));
    ui->listWidget->setGridSize(QSize(100, 100));
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setWordWrap(true);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->listWidget->setStyleSheet(
        "QListWidget::item {"
        "   border: 1px solid #444;"
        "   border-radius: 6px;"
        "   padding: 4px;"
        "   margin: 4px;"
        "   background-color: #2b2b2b;"
        "}"
        "QListWidget::item:hover {"
        "   border: 1px solid #007acc;"
        "   background-color: #3a3a3a;"
        "}"
        "QListWidget::item:selected {"
        "   border: 2px solid #0099ff;"
        "   background-color: #454545;"
        "}"
        );
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragOnly);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);

    ui->imageLabel->setAcceptDrops(true);
    ui->imageLabel->setAcceptDrops(true);
    ui->imageLabel->installEventFilter(this);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    delete ui->scrollAreaWidgetContents->layout();
    QHBoxLayout *layout = new QHBoxLayout(ui->scrollAreaWidgetContents);

    layout->setSpacing(15);
    layout->setContentsMargins(10, 10, 10, 10);

    QList<QPushButton*> buttons = ui->scrollAreaWidgetContents->findChildren<QPushButton*>();
    int totalWidth = 20;

    for (QPushButton *btn : buttons) {
        btn->setFixedWidth(120);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        if (ui->scrollAreaWidgetContents->layout()) {
            ui->scrollAreaWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
        }
        layout->addWidget(btn);
        totalWidth += 120 + 20;
    }
    ui->scrollAreaWidgetContents->setGeometry(0, 0, qMax(totalWidth + 50, 1000), 70);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage convertToQImage(const Image& img) {
    if (img.imageData == nullptr) return QImage();

    QImage qImg(img.imageData, img.width, img.height, img.width * img.channels, QImage::Format_RGB888);

    return qImg.copy();
}

void MainWindow::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose an image", "", "Image Files (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        try {
            saveCurrentState();

            currentImage.loadNewImage(fileName.toStdString());
            originalImage = currentImage;

            activeFilePath = fileName;

            history.clear();
            history.setInitialState(currentImage);
            editedImage = tempImage = currentImage;

            imageStates[activeFilePath] = {originalImage, currentImage, editedImage, tempImage, history};

            QListWidgetItem *item = new QListWidgetItem();
            item->setIcon(QIcon(fileName));
            item->setText(QFileInfo(fileName).fileName());
            item->setData(Qt::UserRole, fileName);

            ui->listWidget->addItem(item);
            ui->listWidget->setCurrentItem(item);

        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "error", e.what());
            return;
        }
    }

    resetAllSliders();
}


void MainWindow::on_btnApplyFilter_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first.!");
        return;
    }
    tempImage = editedImage;
    Invert(tempImage);

    displayCurrentImage(tempImage);
    resetAllSliders();
}
void MainWindow::on_btnSave_clicked()
{
    if (editedImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "There is no image to save!");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(
        this,
        "Save image",
        "",
        "PNG Image (*.png);;JPG Image (*.jpg);;BMP Image (*.bmp)"
        );

    if (!savePath.isEmpty()) {
        try {
            bool success = editedImage.saveImage(savePath.toStdString());

            if (success) {
                QMessageBox::information(this, "success", "The image has been saved successfully.");
                isModified = false;
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "error", e.what());
        }
    }

    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    resetAllSliders();
}

void MainWindow::on_btnToggleMenu_clicked()
{
    isSidebarExpanded = !isSidebarExpanded;

    int startWidth = ui->sidebarFrame->width();
    int endWidth = isSidebarExpanded ? 250 : 58;

    ui->sidebarFrame->setMaximumWidth(isSidebarExpanded ? 250 : 50);

    if (isSidebarExpanded) {
        ui->leftPanelWidget->setVisible(true);
    } else {
        ui->leftPanelWidget->setVisible(false);
    }

    QPropertyAnimation *animation = new QPropertyAnimation(ui->sidebarFrame, "maximumWidth");
    animation->setDuration(300);
    animation->setStartValue(startWidth);
    animation->setEndValue(endWidth);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

    void MainWindow::on_blurslider_valueChanged(int value)
    {
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->blurvalue->blockSignals(true);
    ui->blurvalue->setValue(value);
    ui->blurvalue->blockSignals(false);

    double percentage = static_cast<double>(value);

    tempImage = editedImage;

    blur(tempImage, percentage);

    displayCurrentImage(tempImage);
}

void MainWindow::on_blurvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->blurslider->blockSignals(true);
    ui->blurslider->setValue(arg1);
    ui->blurslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);
    tempImage = editedImage;

    blur(tempImage, percentage);

    QImage qimg(tempImage.imageData, tempImage.width, tempImage.height, tempImage.width * 3, QImage::Format_RGB888);

    QPixmap pixmap = QPixmap::fromImage(qimg);
    QPixmap scaledPixmap = pixmap.scaled(ui->imageLabel->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);

    displayCurrentImage(tempImage);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString filePath = item->data(Qt::UserRole).toString();
    if (filePath.isEmpty()) return;

    void saveCurrentState();

    if (!activeFilePath.isEmpty()) {
        imageStates[activeFilePath] = {originalImage, currentImage, editedImage, tempImage, history};
    }

    if (imageStates.contains(filePath)) {
        ImageState state = imageStates[filePath];

        originalImage = state.originalImage;
        currentImage = state.currentImage;
        editedImage = state.editedImage;
        tempImage = state.tempImage;
        history = state.history;

        displayCurrentImage(editedImage);
    }
    else {
        try {
            currentImage.loadNewImage(filePath.toStdString());
            originalImage = currentImage;

            history.clear();
            history.setInitialState(currentImage);

            editedImage = tempImage = currentImage;

            displayCurrentImage(currentImage);

            imageStates[filePath] = {originalImage, currentImage, editedImage, tempImage, history};
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "error", e.what());
            return;
        }
    }

    activeFilePath = filePath;

    resetAllSliders();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->imageLabel->viewport()) {

        if (isCroppingMode) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    cropStartPoint = mouseEvent->pos();
                    if (!rubberBand) {
                        rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->imageLabel->viewport());
                    }
                    rubberBand->setGeometry(QRect(cropStartPoint, QSize()));
                    rubberBand->show();
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseMove) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (rubberBand && (mouseEvent->buttons() & Qt::LeftButton)) {
                    QPoint currentPoint = mouseEvent->pos();
                    currentPoint.setX(qBound(0, currentPoint.x(), ui->imageLabel->viewport()->width()));
                    currentPoint.setY(qBound(0, currentPoint.y(), ui->imageLabel->viewport()->height()));

                    rubberBand->setGeometry(QRect(cropStartPoint, currentPoint).normalized());
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton && rubberBand) {
                    finalCropRect = rubberBand->geometry();

                    if (finalCropRect.width() > 5 && finalCropRect.height() > 5) {
                        QPointF topLeftScene = ui->imageLabel->mapToScene(ui->imageLabel->viewport()->mapTo(ui->imageLabel, finalCropRect.topLeft()));
                        QPointF bottomRightScene = ui->imageLabel->mapToScene(ui->imageLabel->viewport()->mapTo(ui->imageLabel, finalCropRect.bottomRight()));

                        int x = qMax(0, static_cast<int>(topLeftScene.x()));
                        int y = qMax(0, static_cast<int>(topLeftScene.y()));
                        int w = static_cast<int>(bottomRightScene.x() - topLeftScene.x());
                        int h = static_cast<int>(bottomRightScene.y() - topLeftScene.y());

                        w = qMin(w, editedImage.width - x);
                        h = qMin(h, editedImage.height - y);

                        if (w > 0 && h > 0) {
                            crop(editedImage, x, y, w, h);
                            displayCurrentImage(editedImage);
                        }
                        tempImage = editedImage;
                    }

                    isCroppingMode = false;
                    ui->imageLabel->viewport()->unsetCursor();
                    if (rubberBand) rubberBand->hide();

                    return true;
                }
            }
        }

        if (!isCroppingMode) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    displayCurrentImage(originalImage);
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    displayCurrentImage(editedImage);
                    return true;
                }
            }
        }

        if (event->type() == QEvent::DragEnter || event->type() == QEvent::DragMove) {
            QDragEnterEvent *dragEvent = static_cast<QDragEnterEvent*>(event);
            dragEvent->acceptProposedAction();
            return true;
        }
        else if (event->type() == QEvent::Drop) {
            QDropEvent *dropEvent = static_cast<QDropEvent*>(event);
            dropEvent->acceptProposedAction();

            QListWidgetItem *item = ui->listWidget->currentItem();
            if (item) {
                QString filePath = item->data(Qt::UserRole).toString();
                if (!filePath.isEmpty()) {
                    try {
                        currentImage.loadNewImage(filePath.toStdString());
                        originalImage = currentImage;
                        history.setInitialState(currentImage);

                        editedImage = tempImage = currentImage;
                        QImage qImg = convertToQImage(currentImage);

                        displayCurrentImage(tempImage);

                    }
                    catch (const std::exception& e) {
                        QMessageBox::critical(this, "error", e.what());
                    }
                }
            }
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::on_black_and_white_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    tempImage = editedImage;

    black_and_white(tempImage);


    displayCurrentImage(tempImage);

    resetAllSliders();

}


void MainWindow::on_grayscale_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    tempImage = editedImage;

    grayscale(tempImage);

    displayCurrentImage(tempImage);

    resetAllSliders();
}


void MainWindow::on_Invert_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    tempImage = editedImage;

    Invert(tempImage);

    displayCurrentImage(tempImage);

    resetAllSliders();

}


void MainWindow::on_btnCropRotateToggle_clicked()
{
    bool isVisible = ui->cropRotateContainer->isVisible();

    ui->cropRotateContainer->setVisible(!isVisible);

    if (isVisible) {
        ui->btnCropRotateToggle->setText("Flip ∨");
    } else {
        ui->btnCropRotateToggle->setText("Flip ∧");
    }
}

void MainWindow::on_Detact_Image_Edges_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    Detact_Image_Edges(tempImage);

    displayCurrentImage(tempImage);
    resetAllSliders();
}


void MainWindow::on_flip_Horizontally_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    tempImage = editedImage;

    flip(tempImage, false);

    displayCurrentImage(tempImage);

    on_apply_clicked();
}

void MainWindow::on_newimage_small_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose an image", "", "Image Files (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(QIcon(fileName));
        item->setText(QFileInfo(fileName).fileName());
        item->setData(Qt::UserRole, fileName);

        ui->listWidget->addItem(item);

        displayCurrentImage(currentImage);
    }
    resetAllSliders();
}


void MainWindow::on_lightenDarkenSlider_valueChanged(int value)
{

    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    if (value != 0) {
        int change = (value > 0) ? 1 : 2;
        int rate = std::abs(value);

        tempImage = editedImage;

        lighten_darken(tempImage, change, rate);
    }

    displayCurrentImage(tempImage);
}


// void MainWindow::on_lightenDarkenSpinBox_textChanged(const QString &arg1)
// {
//     if (currentImage.imageData == nullptr) {
//         QMessageBox::warning(this, "alert", "Please select an image first!");
//         return;
//     }
// }


void MainWindow::on_lightenDarkenSpinBox_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->lightenDarkenSlider->blockSignals(true);
    ui->lightenDarkenSlider->setValue(arg1);
    ui->lightenDarkenSlider->blockSignals(false);

    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    if (arg1 != 0) {
        on_lightenDarkenSlider_valueChanged(arg1);
    }

    displayCurrentImage(tempImage);

}


void MainWindow::on_sepia_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    sepia(tempImage);

    displayCurrentImage(tempImage);
    resetAllSliders();
}




void MainWindow::on_televisions_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    televisions(tempImage);

    displayCurrentImage(tempImage);

    resetAllSliders();
}


void MainWindow::on_infrared_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    infrared(tempImage);

    displayCurrentImage(tempImage);

    resetAllSliders();
}



void MainWindow::on_flip_vertically_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    tempImage = editedImage;

    flip(tempImage, true);

    displayCurrentImage(tempImage);

    on_apply_clicked();
}

void MainWindow::on_frama_down_clicked()
{
    bool isVisible = ui->frameContainer->isVisible();
    ui->frameContainer->setVisible(!isVisible);

    if (isVisible) {
        ui->frama_down->setText("Frame V");
    } else {
        ui->frama_down->setText("Frame ^");
    }
}

void MainWindow::on_OilPainting_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    OilPainting(tempImage);

    displayCurrentImage(tempImage);
    resetAllSliders();
}

void MainWindow::on_rotate90_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    rotate(tempImage , 90);

    displayCurrentImage(tempImage);

    on_apply_clicked();

}

void MainWindow::on_rotate270_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    rotate(tempImage , 270);

    displayCurrentImage(tempImage);

    on_apply_clicked();
}

void MainWindow::on_simple_frame_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    QColor color = QColorDialog::getColor(Qt::red, this, "Select Frame Color");

    if (color.isValid()) {
        int r = color.red();
        int g = color.green();
        int b = color.blue();

        tempImage = editedImage;

        frame(tempImage, 1, r, g, b);

        displayCurrentImage(tempImage);
    }
    resetAllSliders();
}

void MainWindow::on_fancy_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    QColor color = QColorDialog::getColor(Qt::red, this, "Select Frame Color");

    if (color.isValid()) {
        int r = color.red();
        int g = color.green();
        int b = color.blue();

        tempImage = editedImage;

        frame(tempImage, 2, r, g, b);

        displayCurrentImage(tempImage);
    }
    resetAllSliders();
}

void MainWindow::on_purple_effect_slider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->purplevalue->blockSignals(true);
    ui->purplevalue->setValue(value);
    ui->purplevalue->blockSignals(false);

    double percentage = static_cast<double>(value);
    tempImage = editedImage;

    purple_effect(tempImage, percentage);

    displayCurrentImage(tempImage);
}

void MainWindow::on_purplevalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->purple_effect_slider->blockSignals(true);
    ui->purple_effect_slider->setValue(arg1);
    ui->purple_effect_slider->blockSignals(false);

    double percentage = static_cast<double>(arg1);
    tempImage = editedImage;

    purple_effect(tempImage, percentage);

    displayCurrentImage(tempImage);
}

void MainWindow::on_crop_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "Alert", "Please select an image first!");
        return;
    }

    isCroppingMode = true;

    ui->imageLabel->setDragMode(QGraphicsView::NoDrag);
    ui->imageLabel->viewport()->setCursor(Qt::CrossCursor);

    ui->imageLabel->viewport()->installEventFilter(this);

    QMessageBox::information(this, "Crop", "Drag with your mouse over the image to select the area.");
    resetAllSliders();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (isCroppingMode) {
        QPoint viewPos = ui->imageLabel->mapFrom(this, event->pos());
        if (ui->imageLabel->rect().contains(viewPos)) {
            cropStartPoint = viewPos;
            if (!rubberBand) {
                rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->imageLabel);
            }
            rubberBand->setGeometry(QRect(cropStartPoint, QSize()));
            rubberBand->show();
            return;
        }
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isCroppingMode && rubberBand && (event->buttons() & Qt::LeftButton)) {
        QPoint currentPoint = ui->imageLabel->mapFrom(this, event->pos());

        currentPoint.setX(qBound(0, currentPoint.x(), ui->imageLabel->width()));
        currentPoint.setY(qBound(0, currentPoint.y(), ui->imageLabel->height()));

        rubberBand->setGeometry(QRect(cropStartPoint, currentPoint).normalized());
    }

    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::on_resizeButton_clicked()
{
    if (editedImage.imageData == nullptr) {
        QMessageBox::warning(this, "Alert", "Please select an image first!");
        return;
    }

    QDialog resizeDialog(this);
    resizeDialog.setWindowTitle("Resize");
    resizeDialog.setFixedSize(360, 280);

    QVBoxLayout *mainLayout = new QVBoxLayout(&resizeDialog);

    QHBoxLayout *modeLayout = new QHBoxLayout();
    QRadioButton *radioPixels = new QRadioButton("Pixels", &resizeDialog);
    QRadioButton *radioPercentage = new QRadioButton("Percentage", &resizeDialog);
    radioPixels->setChecked(true);

    modeLayout->addWidget(radioPixels);
    modeLayout->addWidget(radioPercentage);
    mainLayout->addLayout(modeLayout);

    QHBoxLayout *inputsLayout = new QHBoxLayout();

    QVBoxLayout *widthLayout = new QVBoxLayout();
    QLabel *lblWidth = new QLabel("Width (px)", &resizeDialog);
    QLineEdit *txtWidth = new QLineEdit(&resizeDialog);
    txtWidth->setText(QString::number(editedImage.width));
    widthLayout->addWidget(lblWidth);
    widthLayout->addWidget(txtWidth);

    QVBoxLayout *heightLayout = new QVBoxLayout();
    QLabel *lblHeight = new QLabel("Height (px)", &resizeDialog);
    QLineEdit *txtHeight = new QLineEdit(&resizeDialog);
    txtHeight->setText(QString::number(editedImage.height));
    heightLayout->addWidget(lblHeight);
    heightLayout->addWidget(txtHeight);

    inputsLayout->addLayout(widthLayout);
    inputsLayout->addLayout(heightLayout);
    mainLayout->addLayout(inputsLayout);

    QVBoxLayout *infoLayout = new QVBoxLayout();
    QLabel *lblCurrentSize = new QLabel(QString("Current: %1 x %2 pixels").arg(editedImage.width).arg(editedImage.height), &resizeDialog);
    QLabel *lblNewSize = new QLabel(&resizeDialog);

    infoLayout->addWidget(lblCurrentSize);
    infoLayout->addWidget(lblNewSize);
    mainLayout->addLayout(infoLayout);

    auto updateNewDimensions = [&]() {
        bool okW, okH;
        double valW = txtWidth->text().toDouble(&okW);
        double valH = txtHeight->text().toDouble(&okH);

        int calcW = editedImage.width;
        int calcH = editedImage.height;

        if (okW && okH) {
            if (radioPercentage->isChecked()) {
                calcW = static_cast<int>((editedImage.width * valW) / 100.0);
                calcH = static_cast<int>((editedImage.height * valH) / 100.0);
            } else {
                calcW = static_cast<int>(valW);
                calcH = static_cast<int>(valH);
            }
        }
        if (calcW < 1) calcW = 1;
        if (calcH < 1) calcH = 1;

        lblNewSize->setText(QString("New:     %1 x %2 pixels").arg(calcW).arg(calcH));
    };

    connect(txtWidth, &QLineEdit::textChanged, updateNewDimensions);
    connect(txtHeight, &QLineEdit::textChanged, updateNewDimensions);

    connect(radioPixels, &QRadioButton::toggled, [&](bool checked) {
        if (checked) {
            lblWidth->setText("Width (px)");
            lblHeight->setText("Height (px)");
            txtWidth->setText(QString::number(editedImage.width));
            txtHeight->setText(QString::number(editedImage.height));
        }
    });

    connect(radioPercentage, &QRadioButton::toggled, [&](bool checked) {
        if (checked) {
            lblWidth->setText("Width (%)");
            lblHeight->setText("Height (%)");
            txtWidth->setText("100");
            txtHeight->setText("100");
        }
    });

    updateNewDimensions();

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnSave = new QPushButton("Save", &resizeDialog);
    QPushButton *btnCancel = new QPushButton("Cancel", &resizeDialog);
    btnLayout->addWidget(btnSave);
    btnLayout->addWidget(btnCancel);
    mainLayout->addLayout(btnLayout);

    connect(btnCancel, &QPushButton::clicked, &resizeDialog, &QDialog::reject);

    int final_width = editedImage.width;
    int final_height = editedImage.height;

    connect(btnSave, &QPushButton::clicked, [&]() {
        bool okW, okH;
        double valW = txtWidth->text().toDouble(&okW);
        double valH = txtHeight->text().toDouble(&okH);

        if (!okW || !okH || valW <= 0 || valH <= 0) {
            QMessageBox::warning(&resizeDialog, "Error", "Please enter valid numbers!");
            return;
        }

        if (radioPercentage->isChecked()) {
            final_width = static_cast<int>((editedImage.width * valW) / 100.0);
            final_height = static_cast<int>((editedImage.height * valH) / 100.0);
        } else {
            final_width = static_cast<int>(valW);
            final_height = static_cast<int>(valH);
        }

        if (final_width < 1) final_width = 1;
        if (final_height < 1) final_height = 1;

        resizeDialog.accept();
    });

    if (resizeDialog.exec() == QDialog::Accepted) {
        tempImage = editedImage;
        ::resize(tempImage, final_width, final_height);
        on_apply_clicked();
    }
}

void MainWindow::on_skewButton_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "Alert", "Please select an image first!");
        return;
    }

    bool ok;
    double degree = QInputDialog::getDouble(this,
                                            "Skew Image",
                                            "Enter skew angle in degrees:",
                                            0,
                                            -360.0,
                                            360.0,
                                            1,
                                            &ok);
    if (ok && degree != 0) {
        skewImage(tempImage, degree);

        displayCurrentImage(tempImage);
    }
    resetAllSliders();
}



void MainWindow::on_mergeButton_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "Alert", "Please load a main image first!");
        return;
    }

    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    if (selectedItem == nullptr) {
        QMessageBox::warning(this, "Alert", "Please select a second image from the list first!");
        return;
    }

    QString fullPath = selectedItem->data(Qt::UserRole).toString();

    if (fullPath.isEmpty()) {
        fullPath = selectedItem->text();
    }

    try {
        Image image2(fullPath.toStdString());

        if (image2.imageData == nullptr) {
            QMessageBox::critical(this, "Error", "File does not exist or couldn't be loaded!");
            return;
        }

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Resize Option",
                                                                  "Resize both images to same dimensions before merging?",
                                                                  QMessageBox::Yes | QMessageBox::No);

        bool apply_resize = (reply == QMessageBox::Yes);

        ::merge(tempImage, image2, apply_resize);

        displayCurrentImage(tempImage);

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "File Error", QString("Could not load image: %1").arg(e.what()));
    }
    resetAllSliders();
}

void MainWindow::displayCurrentImage(Image image)
{
    if (image.imageData == nullptr) return;

    QImage qimg(image.imageData, image.width, image.height, image.width * 3, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimg);

    QSize targetSize = ui->imageLabel->contentsRect().size();
    if (targetSize.width() < 50 || targetSize.height() < 50) {
        if (ui->imageLabel->parentWidget()) {
            targetSize = ui->imageLabel->parentWidget()->contentsRect().size();
        }
    }

    if (!scene) {
        scene = new QGraphicsScene(this);
        ui->imageLabel->setScene(scene);
    }

    scene->clear();
    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());

    ui->imageLabel->fitInView(pixmap.rect(), Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (currentImage.imageData != nullptr) {
        displayCurrentImage(tempImage);
    }
    resetAllSliders();
}

void MainWindow::on_btnApplydarkTheme_clicked()
{
    QString darkTheme = R"(
    QMainWindow {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                          stop:0 #060913,
                                          stop:0.5 #0a1128,
                                          stop:1 #04060b);
        color: #f5f5f7;
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    }

    /* توحيد الخلفية والشفافية لكل الإطارات واللوحات في التطبيق (اليمين واليسار) */
    QFrame, QWidget#sidebarFrame, QWidget#rightPanelWidget,
    QScrollArea, QScrollArea > QWidget > QWidget {
        background-color: rgba(16, 24, 44, 0.55);
        border: 1px solid rgba(255, 255, 255, 0.1);
        border-radius: 16px;
    }

    /* توحيد خلفية النصوص لتكون شفافة تماماً */
    QLabel {
        background-color: transparent;
        color: #f5f5f7;
        border: none;
        padding: 2px 0px;
    }

    /* الأزرار العادية */
    QPushButton {
        background-color: rgba(30, 41, 59, 0.45);
        color: #f5f5f7;
        border: 1px solid rgba(255, 255, 255, 0.08);
        border-radius: 10px;
        padding: 8px 14px;
        font-weight: 500;
    }
    QPushButton:hover {
        background-color: rgba(0, 113, 227, 0.25);
        border-color: rgba(0, 113, 227, 0.4);
    }
    QPushButton:pressed {
        background-color: rgba(0, 113, 227, 0.4);
    }

    /* زر الحفظ المميز */
    QPushButton#saveButton {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                          stop:0 #0071e3,
                                          stop:1 #005bb5);
        color: white;
        border: 1px solid rgba(255, 255, 255, 0.25);
        border-radius: 10px;
    }

    /* القوائم الجانبية */
    QListWidget {
        background-color: rgba(10, 15, 28, 0.4);
        color: #f5f5f7;
        border: 1px solid rgba(255, 255, 255, 0.06);
        border-radius: 12px;
        padding: 4px;
    }
    QListWidget::item {
        background-color: transparent;
        border-radius: 8px;
        padding: 6px;
        margin-bottom: 3px;
    }
    QListWidget::item:selected {
        background-color: rgba(0, 113, 227, 0.6);
        color: white;
        border: 1px solid rgba(255, 255, 255, 0.15);
    }

    /* منطقة عرض الصورة */
    QGraphicsView {
        background-color: rgba(5, 8, 15, 0.6);
        border: 1px solid rgba(255, 255, 255, 0.08);
        border-radius: 16px;
    }

    /* أشرطة التمرير (Sliders) */
    QSlider::groove:horizontal {
        background: rgba(255, 255, 255, 0.08);
        height: 6px;
        border-radius: 3px;
    }
    QSlider::sub-page:horizontal {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #0071e3, stop:1 #47a3ff);
        border-radius: 3px;
    }
    QSlider::handle:horizontal {
        background: #ffffff;
        width: 16px;
        height: 16px;
        margin: -5px 0;
        border-radius: 8px;
        border: 2px solid #0071e3;
    }
)";

    QPixmap pix270 = ui->rotate270->icon().pixmap(24, 24);
    if (!pix270.isNull()) {
        QPixmap tinted270(24, 24);
        tinted270.fill(Qt::transparent);
        QPainter p270(&tinted270);
        p270.drawPixmap(0, 0, pix270);
        p270.setCompositionMode(QPainter::CompositionMode_SourceIn);
        p270.fillRect(tinted270.rect(), Qt::white);
        p270.end();
        ui->rotate270->setIcon(QIcon(tinted270));
    }

    QPixmap pix90 = ui->rotate90->icon().pixmap(24, 24);
    if (!pix90.isNull()) {
        QPixmap tinted90(24, 24);
        tinted90.fill(Qt::transparent);
        QPainter p90(&tinted90);
        p90.drawPixmap(0, 0, pix90);
        p90.setCompositionMode(QPainter::CompositionMode_SourceIn);
        p90.fillRect(tinted90.rect(), Qt::white);
        p90.end();
        ui->rotate90->setIcon(QIcon(tinted90));
    }

    this->setStyleSheet(darkTheme);
}

void MainWindow::on_btnApplyLightTheme_clicked()
{
    QString lightTheme = R"(
    /* النافذة الرئيسية مع خلفية متدرجة فاتحة وناعمة */
    QMainWindow {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                            stop:0 #f0f4f8,
                                            stop:0.5 #e2e8f0,
                                            stop:1 #cbd5e1);
        color: #1e293b;
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    }

    /* اللوحات الجانبية والإطارات بتأثير الزجاج الفاتح الشفاف */
    QFrame, QWidget#sidebarFrame, QWidget#rightPanelWidget,
    QScrollArea, QScrollArea > QWidget > QWidget {
        background-color: rgba(255, 255, 255, 0.65);
        border: 1px solid rgba(255, 255, 255, 0.8);
        border-radius: 16px;
    }

    /* توحيد خلفية النصوص لتكون شفافة تماماً بدون مربعات */
    QLabel {
        background-color: transparent;
        color: #1e293b;
        border: none;
        padding: 2px 0px;
        font-weight: 500;
    }

    /* الأزرار العادية في الوضع الفاتح */
    QPushButton {
        background-color: rgba(255, 255, 255, 0.7);
        color: #1e293b;
        border: 1px solid rgba(203, 213, 225, 0.6);
        border-radius: 10px;
        padding: 8px 14px;
        font-weight: 500;
    }
    QPushButton:hover {
        background-color: rgba(0, 113, 227, 0.15);
        border-color: rgba(0, 113, 227, 0.4);
        color: #0071e3;
    }
    QPushButton:pressed {
        background-color: rgba(0, 113, 227, 0.25);
    }

    /* زر الحفظ المميز بلون أبل الأزرق المشرق */
    QPushButton#saveButton {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                            stop:0 #0071e3,
                                            stop:1 #005bb5);
        color: white;
        border: 1px solid rgba(0, 113, 227, 0.3);
        border-radius: 10px;
    }
    QPushButton#saveButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                            stop:0 #0077ed,
                                            stop:1 #0062c4);
    }

    /* القوائم الجانبية */
    QListWidget {
        background-color: rgba(255, 255, 255, 0.5);
        color: #1e293b;
        border: 1px solid rgba(203, 213, 225, 0.5);
        border-radius: 12px;
        padding: 4px;
    }
    QListWidget::item {
        background-color: transparent;
        border-radius: 8px;
        padding: 6px;
        margin-bottom: 3px;
    }
    QListWidget::item:selected {
        background-color: rgba(0, 113, 227, 0.85);
        color: white;
        border: none;
    }

    /* منطقة عرض الصورة */
    QGraphicsView {
        background-color: rgba(241, 245, 249, 0.8);
        border: 1px solid rgba(203, 213, 225, 0.6);
        border-radius: 16px;
    }

    /* أشرطة التمرير (Sliders) في الوضع الفاتح */
    QSlider::groove:horizontal {
        background: rgba(203, 213, 225, 0.6);
        height: 6px;
        border-radius: 3px;
    }
    QSlider::sub-page:horizontal {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #0071e3, stop:1 #38bdf8);
        border-radius: 3px;
    }
    QSlider::handle:horizontal {
        background: #ffffff;
        width: 16px;
        height: 16px;
        margin: -5px 0;
        border-radius: 8px;
        border: 2px solid #0071e3;
    }

    /* تنسيق مربعات الأرقام (QSpinBox) بجانب السلايدرات لضمان ظهورها بوضوح */
    QSpinBox {
        background-color: rgba(255, 255, 255, 0.85);
        color: #1e293b;
        border: 1px solid rgba(203, 213, 225, 0.8);
        border-radius: 6px;
        padding: 2px 6px;
        font-weight: 600;
    }
    QSpinBox::up-button, QSpinBox::down-button {
        background-color: rgba(241, 245, 249, 0.9);
        border: 1px solid rgba(203, 213, 225, 0.6);
        width: 16px;
        border-radius: 3px;
    }
    QSpinBox::up-button:hover, QSpinBox::down-button:hover {
        background-color: rgba(0, 113, 227, 0.2);
    }
)";

    QPixmap pix270 = ui->rotate270->icon().pixmap(24, 24);
    if (!pix270.isNull()) {
        QPixmap tinted270(24, 24);
        tinted270.fill(Qt::transparent);
        QPainter p270(&tinted270);
        p270.drawPixmap(0, 0, pix270);
        p270.setCompositionMode(QPainter::CompositionMode_SourceIn);
        p270.fillRect(tinted270.rect(), Qt::black);
        p270.end();
        ui->rotate270->setIcon(QIcon(tinted270));
    }

    QPixmap pix90 = ui->rotate90->icon().pixmap(24, 24);
    if (!pix90.isNull()) {
        QPixmap tinted90(24, 24);
        tinted90.fill(Qt::transparent);
        QPainter p90(&tinted90);
        p90.drawPixmap(0, 0, pix90);
        p90.setCompositionMode(QPainter::CompositionMode_SourceIn);
        p90.fillRect(tinted90.rect(), Qt::black);
        p90.end();
        ui->rotate90->setIcon(QIcon(tinted90));
    }

    this->setStyleSheet(lightTheme);
}

void MainWindow::on_pixlatedslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->pixlatedvalue->blockSignals(true);
    ui->pixlatedvalue->setValue(value);
    ui->pixlatedvalue->blockSignals(false);

    double percentage = static_cast<double>(value);

    tempImage = editedImage;

    pixelated(tempImage, percentage);

    displayCurrentImage(tempImage);
}


void MainWindow::on_pixlatedvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->pixlatedvalue->blockSignals(true);
    ui->pixlatedvalue->setValue(arg1);
    ui->pixlatedvalue->blockSignals(false);

    double percentage = static_cast<double>(arg1);
    tempImage = editedImage;

    pixelated(tempImage, percentage);

    displayCurrentImage(tempImage);
}


void MainWindow::on_vignetteslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->vignettevalue->blockSignals(true);
    ui->vignettevalue->setValue(value);
    ui->vignettevalue->blockSignals(false);

    double percentage = static_cast<double>(value);

    tempImage = editedImage;

    vignette(tempImage, percentage);

    displayCurrentImage(tempImage);
}




void MainWindow::on_vignettevalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->vignetteslider->blockSignals(true);
    ui->vignetteslider->setValue(arg1);
    ui->vignetteslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);
    tempImage = editedImage;

    vignette(tempImage, percentage);

    displayCurrentImage(tempImage);
}



void MainWindow::on_RGB_clicked()
{
    bool isVisible = ui->RGB_widget->isVisible();

    ui->RGB_widget->setVisible(!isVisible);

    if (isVisible) {
        ui->RGB->setText("RGB ∨");
    } else {
        ui->RGB->setText("RGB ∧");
    }
}




void MainWindow::on_wave_clicked()
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "please select an image first!");
        return;
    }

    tempImage = editedImage;

    wave(tempImage);

    displayCurrentImage(tempImage);
    resetAllSliders();
}




void MainWindow::on_contrastslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->contrastvalue->blockSignals(true);
    ui->contrastvalue->setValue(value);
    ui->contrastvalue->blockSignals(false);


    if (value != 0) {
        int change = (value > 0) ? 1 : 2;
        int rate = std::abs(value);
        if (change == 2){
            rate = -rate;
        }

        tempImage = editedImage;

        contrast(tempImage, rate);
    }

    displayCurrentImage(tempImage);
}




void MainWindow::on_contrastvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->contrastslider->blockSignals(true);
    ui->contrastslider->setValue(arg1);
    ui->contrastslider->blockSignals(false);
    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    contrast(tempImage, percentage);

    displayCurrentImage(tempImage);
}


void MainWindow::on_saturationslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->saturationvalue->blockSignals(true);
    ui->saturationvalue->setValue(value);
    ui->saturationvalue->blockSignals(false);

    tempImage = editedImage;

    if (value != 0) {
        double factor = static_cast<double>(value);
        saturation(tempImage, factor);
    }

    displayCurrentImage(tempImage);
}


void MainWindow::on_saturationvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->saturationslider->blockSignals(true);
    ui->saturationslider->setValue(arg1);
    ui->saturationslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    if (arg1 != 0) {
        saturation(tempImage, percentage);
    }

    displayCurrentImage(tempImage);
}

void MainWindow::on_redslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->redvalue->blockSignals(true);
    ui->redvalue->setValue(value);
    ui->redvalue->blockSignals(false);

    tempImage = editedImage;

    if (value != 0) {
        double factor = static_cast<double>(value);
        RGB(tempImage, value,0);
    }

    displayCurrentImage(tempImage);
}


void MainWindow::on_redvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->redslider->blockSignals(true);
    ui->redslider->setValue(arg1);
    ui->redslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    if (arg1 != 0) {
        RGB(tempImage, arg1, 0);
    }

    displayCurrentImage(tempImage);
}


void MainWindow::on_greenslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->greenvalue->blockSignals(true);
    ui->greenvalue->setValue(value);
    ui->greenvalue->blockSignals(false);

    tempImage = editedImage;

    if (value != 0) {
        double factor = static_cast<double>(value);
        RGB(tempImage, value,1);
    }

    displayCurrentImage(tempImage);
}

void MainWindow::on_greenvalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->greenslider->blockSignals(true);
    ui->greenslider->setValue(arg1);
    ui->greenslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    if (arg1 != 0) {
        RGB(tempImage, arg1, 1);
    }

    displayCurrentImage(tempImage);
}


void MainWindow::on_blueslider_valueChanged(int value)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }
    ui->bluevalue->blockSignals(true);
    ui->bluevalue->setValue(value);
    ui->bluevalue->blockSignals(false);

    tempImage = editedImage;

    if (value != 0) {
        double factor = static_cast<double>(value);
        RGB(tempImage, value,2);
    }

    displayCurrentImage(tempImage);
}


void MainWindow::on_bluevalue_valueChanged(int arg1)
{
    if (currentImage.imageData == nullptr) {
        QMessageBox::warning(this, "alert", "Please select an image first!");
        return;
    }

    ui->blueslider->blockSignals(true);
    ui->blueslider->setValue(arg1);
    ui->blueslider->blockSignals(false);

    double percentage = static_cast<double>(arg1);

    tempImage = editedImage;

    if (arg1 != 0) {
        RGB(tempImage, arg1, 2);
    }

    displayCurrentImage(tempImage);
}

void MainWindow::on_btnUndo_clicked()
{
    if (history.undo(editedImage)) {
        displayCurrentImage(editedImage);
    } else {
        displayCurrentImage(editedImage);
    }
    resetAllSliders();
}


void MainWindow::on_btnRedo_clicked()
{
    if (history.redo(editedImage)) {
        displayCurrentImage(editedImage);
    }
    resetAllSliders();
}

void MainWindow::on_apply_clicked()
{
    if (tempImage.imageData == nullptr) {
        QMessageBox::warning(this, "Alert", "No filter applied yet to commit!");
        return;
    }

    history.recordState(editedImage);

    editedImage = tempImage;

    displayCurrentImage(editedImage);
    isModified = true;
}

void MainWindow::on_btnReset_clicked()
{
    if (history.reset(editedImage)) {
        displayCurrentImage(editedImage);
    }
    resetAllSliders();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        double scaleFactor = 1.15;
        if (event->angleDelta().y() < 0) {
            scaleFactor = 1.0 / scaleFactor;
        }

        ui->imageLabel->scale(scaleFactor, scaleFactor);
        event->accept();
    } else {
        QMainWindow::wheelEvent(event);
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QPoint posInLabel = ui->imageLabel->mapFrom(this, event->pos());

    if (ui->imageLabel->rect().contains(posInLabel)) {
        QListWidgetItem *item = ui->listWidget->currentItem();
        if (item) {
            on_listWidget_itemDoubleClicked(item);
            event->acceptProposedAction();
            return;
        }
    }

    event->ignore();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isModified) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "exit",
                                     "You have unsaved changes.. Are you sure you want to close the program?",
                                     QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}


void MainWindow::resetAllSliders()
{
    QList<QSlider*> sliders = {
        ui->greenslider,
        ui->redslider,
        ui->blueslider,
        ui->saturationslider,
        ui->contrastslider,
        ui->pixlatedslider,
        ui->purple_effect_slider,
        ui->lightenDarkenSlider,
        ui->vignetteslider,
        ui->pixlatedslider,
        ui->blurslider
    };

    QList<QSpinBox*> spinBoxes = {
        ui->greenvalue,
        ui->redvalue,
        ui->bluevalue,
        ui->saturationvalue,
        ui->contrastvalue,
        ui->pixlatedvalue,
        ui->purplevalue,
        ui->lightenDarkenSpinBox,
        ui->vignettevalue,
        ui->pixlatedvalue,
        ui->blurvalue
    };


    for (QSlider* slider : sliders) {
        if (slider) {
            slider->blockSignals(true);
            slider->setValue(0);
            slider->blockSignals(false);
        }
    }


    for (QSpinBox* spinBox : spinBoxes) {
        if (spinBox) {
            spinBox->blockSignals(true);
            spinBox->setValue(0);
            spinBox->blockSignals(false);
        }
    }
}

void MainWindow::saveCurrentState()
{
    if (!activeFilePath.isEmpty()) {
        imageStates[activeFilePath] = {originalImage, currentImage, editedImage, tempImage, history};
    }
}


QPixmap MainWindow::changeIconColor(const QIcon &icon, const QSize &size, const QColor &color) {
    QPixmap pixmap = icon.pixmap(size);

    QPixmap tintedPixmap(size);
    tintedPixmap.fill(Qt::transparent);

    QPainter painter(&tintedPixmap);
    painter.drawPixmap(0, 0, pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(tintedPixmap.rect(), color);
    painter.end();

    return tintedPixmap;
}