#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QLocale>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
class QLineEdit;
QT_END_NAMESPACE

namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    static const QLocale::Language DEFAULT_LANGUAGE;
    static const QColor DEFAULT_BACKGROUND_COLOR;
    static const QColor DEFAULT_TEXT_BACKGROUND_COLOR;
    static const QFont DEFAULT_TEXT_FONT;
    static const QColor DEFAULT_TEXT_COLOR;
    static const QString DEFAULT_APPLICATION_DIRECTORY;
    static const QString DEFAULT_SLIDESHOWS_DIRECTORY;
    static const QString DEFAULT_IMAGES_DIRECTORY;

    static QHash<QAction*, QKeySequence> DefaultShortcuts;
    static void loadAllShortcuts(const QSettings &settings);

    static bool checkDirectory(const QString &directory, bool create = true, bool warningOnFailure = true);

    explicit OptionsDialog(QList<QPair<QString, QList<QAction*> > > *actions, QWidget *parent = 0);
    ~OptionsDialog();

    QLocale::Language language() const;
    QColor backgroundColor() const;
    QColor textBackgroundColor() const;
    QFont textFont() const;
    QColor textColor() const;
    QString slideshowsDirectory() const;
    QString imagesDirectory() const;

private slots:
    void on_backgroundColorPushButton_clicked();
    void on_backgroundColorResetPushButton_clicked();
    void on_textBackgroundColorPushButton_clicked();
    void on_textBackgroundColorResetPushButton_clicked();
    void on_textFontPushButton_clicked();
    void on_textFontResetPushButton_clicked();
    void on_textColorPushButton_clicked();
    void on_textColorResetPushButton_clicked();
    void on_openSlideshowsDirectoryPushButton_clicked();
    void on_slideshowsDirectoryPushButton_clicked();
    void on_openImagesDirectoryPushButton_clicked();
    void on_imagesDirectoryPushButton_clicked();

    void directoryLineEdit_textChanged(const QString &text);

    void on_shortcutsTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_resetAllPushButton_clicked();
    void on_resetPushButton_clicked();
    void on_removePushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::OptionsDialog *ui;
    QList<QPair<QString, QList<QAction*> > > *m_actions;

    void loadSettings();
    void saveSettings();

    void selectColor(QPushButton *pushButton, QColorDialog::ColorDialogOptions options = 0);
    void chooseDirectory(QLineEdit *lineEdit, const QString &defaultDirectory);
    bool checkShortcuts();
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // OPTIONSDIALOG_H
