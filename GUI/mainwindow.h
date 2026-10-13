#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QListWidgetItem>
#include <QRubberBand>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPoint>
#include <QRect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>

#include "Image_Class.h"
#include "imagehistory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    bool isDarkMode = false;
    void closeEvent(QCloseEvent *event) override;
    //bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_lightenDarkenSlider_valueChanged(int value);
    void on_btnCropRotateToggle_clicked();
    void on_btnOpen_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_btnApplyFilter_clicked();
    void on_btnSave_clicked();
    void on_btnToggleMenu_clicked();
    void on_blurslider_valueChanged(int value);
    void on_blurvalue_valueChanged(int arg1);
    // void on_pushButton_clicked();
    void on_black_and_white_clicked();
    void on_grayscale_clicked();
    void on_Invert_clicked();
    void on_Detact_Image_Edges_clicked();
    // void on_flip_clicked();
    void on_newimage_small_clicked();
    // void on_lightenDarkenSpinBox_textChanged(const QString &arg1);
    void on_lightenDarkenSpinBox_valueChanged(int arg1);
    void on_sepia_clicked();
    void on_televisions_clicked();
    void on_infrared_clicked();
    void on_flip_vertically_clicked();
    void on_flip_Horizontally_clicked();
    void on_frama_down_clicked();
    void on_OilPainting_clicked();
    // void on_imageLabel_linkHovered(const QString &link);
    void on_rotate90_clicked();
    void on_rotate270_clicked();
    void on_simple_frame_clicked();
    void on_fancy_clicked();
    void on_purple_effect_slider_valueChanged(int value);
    void on_purplevalue_valueChanged(int arg1);
    void on_crop_clicked();
    void on_resizeButton_clicked();
    void on_skewButton_clicked();
    void on_mergeButton_clicked();

    void on_btnApplydarkTheme_clicked();
    void on_btnApplyLightTheme_clicked();

    // void on_imageLabel_linkActivated(const QString &link);

    // void on_purple_effect_slider_2_valueChanged(int value);

    void on_pixlatedslider_valueChanged(int value);

    void on_pixlatedvalue_valueChanged(int arg1);

    // void on_pixlatedvalue_textChanged(const QString &arg1);

    // void on_blurvalue_textChanged(const QString &arg1);

    void on_vignetteslider_valueChanged(int value);

    // void on_vignettevalue_textChanged(const QString &arg1);

    void on_vignettevalue_valueChanged(int arg1);

    // void on_RGP_clicked();

    void on_RGB_clicked();

    // void on_cropRotateContainer_customContextMenuRequested(const QPoint &pos);

    void on_wave_clicked();

    // void on_lightenDarkenSlider_3_valueChanged(int value);

    // void on_lightenDarkenSpinBox_3_valueChanged(int arg1);

    void on_contrastslider_valueChanged(int value);

    // void on_contrastvalue_textChanged(const QString &arg1);

    void on_contrastvalue_valueChanged(int arg1);

    void on_saturationslider_valueChanged(int value);

    void on_saturationvalue_valueChanged(int arg1);

    void on_redslider_valueChanged(int value);

    void on_redvalue_valueChanged(int arg1);

    void on_greenslider_valueChanged(int value);

    void on_greenvalue_valueChanged(int arg1);

    void on_blueslider_valueChanged(int value);

    void on_bluevalue_valueChanged(int arg1);

    // void on_saturationvalue_textChanged(const QString &arg1);

    void on_btnUndo_clicked();

    void on_btnRedo_clicked();

    void on_apply_clicked();

    void on_btnReset_clicked();

    // void on_purple_effect_slider_actionTriggered(int action);

private:
    Image currentImage;
    Image tempImage;
    Image editedImage;
    Image originalImage;
    Image forSlidersImage;

    bool isModified = false;
    bool isSidebarExpanded = true;
    QPoint cropStartPoint;
    QPoint skewStartPoint;
    QPoint originPoint;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;

    bool isSkewMode = false;
    bool isCroppingMode = false;

    QRubberBand *rubberBand = nullptr;

    ImageHistory history;
    void displayCurrentImage(Image image);

    QRect finalCropRect;

    void resetAllSliders();


    // تعريف هيكل يحفظ حالة الصورة بالكامل
    struct ImageState {
        Image originalImage;
        Image currentImage;
        Image editedImage;
        Image tempImage;
        ImageHistory history;
    };

    // مسار الصورة النشطة حالياً
    QString activeFilePath;

    // خريطة تربط مسار كل صورة بحالتها وهيستوري الخاص بيها
    QMap<QString, ImageState> imageStates;

    void saveCurrentState();

    QPixmap changeIconColor(const QIcon &icon, const QSize &size, const QColor &color);

};

#endif // MAINWINDOW_H