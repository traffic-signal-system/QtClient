#ifndef COMMCLASS_H
#define COMMCLASS_H
#include <QItemDelegate>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>


class ComboxDeligate :public QItemDelegate
{
    Q_OBJECT
public:
    ComboxDeligate(QStringList titleList, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private :
    QStringList strList;
};
//--------------------------------------------------------

class TimeEditDeligate :public QItemDelegate
{
    Q_OBJECT
public:
    TimeEditDeligate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};
////----------------------------------------------------------

//class TreeItem
// {
// public:
//     TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
//     ~TreeItem();

//     TreeItem *child(int number);
//     int childCount() const;
//     int columnCount() const;
//     QVariant data(int column) const;
//     bool insertChildren(int position, int count, int columns);
//     bool insertColumns(int position, int columns);
//     TreeItem *parent();
//     bool removeChildren(int position, int count);
//     bool removeColumns(int position, int columns);
//     int childNumber() const;
//     bool setData(int column, const QVariant &value);

// private:
//     QList<TreeItem*> childItems;
//     QVector<QVariant> itemData;
//     TreeItem *parentItem;
// };
////-----------------------------------------------------------

//class TreeModel : public QAbstractItemModel
// {
//     Q_OBJECT

// public:
//     TreeModel(const QStringList &headers, const QString &data,
//               QObject *parent = 0);
//     ~TreeModel();
//     QVariant data(const QModelIndex &index, int role) const;
//     QVariant headerData(int section, Qt::Orientation orientation,
//                  int role = Qt::DisplayRole) const;

//     QModelIndex index(int row, int column,
//                const QModelIndex &parent = QModelIndex()) const;
//     QModelIndex parent(const QModelIndex &index) const;

//     int rowCount(const QModelIndex &parent = QModelIndex()) const;
//     int columnCount(const QModelIndex &parent = QModelIndex()) const;
//     Qt::ItemFlags flags(const QModelIndex &index) const;
//      bool setData(const QModelIndex &index, const QVariant &value,
//                   int role = Qt::EditRole);
//      bool setHeaderData(int section, Qt::Orientation orientation,
//                         const QVariant &value, int role = Qt::EditRole);

//      bool insertColumns(int position, int columns,
//                         const QModelIndex &parent = QModelIndex());
//      bool removeColumns(int position, int columns,
//                         const QModelIndex &parent = QModelIndex());
//      bool insertRows(int position, int rows,
//                      const QModelIndex &parent = QModelIndex());
//      bool removeRows(int position, int rows,
//                      const QModelIndex &parent = QModelIndex());

//  private:
//      void setupModelData(const QStringList &lines, TreeItem *parent);
//      TreeItem *getItem(const QModelIndex &index) const;

//      TreeItem *rootItem;
//    };

//-----------------------------------------
class CheckGroup : public QGroupBox
{
    Q_OBJECT
public :
    CheckGroup(QStringList labelStrs, QWidget *parent=0);
    CheckGroup(QWidget *parent=0);
    void setCheckBoxes(QStringList labelStrs);
    void setCheckBoxWithTitles(QStringList strTitleList);
    QStringList m_CheckedTitleList;

private :
    QList<QCheckBox *> m_CheckBoxList;

    QPushButton *m_OkPushButton;
    QPushButton *m_CancelPushButton;

private :
    ;

signals :
    ;

public slots :
    void updateCheckBoxes(void);
};


class CheckGroupDeligate :public QItemDelegate
{
    Q_OBJECT
public:
    CheckGroupDeligate(QStringList labelStrs, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private :
    QStringList m_TitleStringList;
//    int minValue;
//    int maxValue;
};
#endif // COMMCLASS_H
