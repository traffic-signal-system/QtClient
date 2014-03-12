#include "CommClass.h"
#include <QComboBox>
#include <QTimeEdit>
#include <QGridLayout>

/*************************************************************/

ComboxDeligate::ComboxDeligate(QStringList titleList, QObject *parent)
    :QItemDelegate(parent)
{
    strList = titleList;
}

QWidget *ComboxDeligate::createEditor(QWidget *parent, const QStyleOptionViewItem &,const QModelIndex &) const
{
    QComboBox *box = new QComboBox(parent);
    box->addItems(strList);
    box->installEventFilter(const_cast <ComboxDeligate*> (this));
    return box;
}

void ComboxDeligate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString editStr = index.model()->data(index).toString();
    QComboBox *box = static_cast <QComboBox*> (editor);
    int i = box->findText(editStr);
    box->setCurrentIndex(i);
}

void ComboxDeligate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast <QComboBox*> (editor);
    model->setData(index, QVariant(box->currentText()));
}

void ComboxDeligate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}


/*************************************************************/

TimeEditDeligate::TimeEditDeligate(QObject *)
{
}

QWidget* TimeEditDeligate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QTimeEdit *editor = new QTimeEdit(parent);
    editor->setDisplayFormat("hh:mm");
    editor->installEventFilter(const_cast<TimeEditDeligate*>(this));
    return editor;
}

void TimeEditDeligate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString timeStr = index.model()->data(index).toString();
    QTime time = QTime::fromString(timeStr,"hh::mm");
    QTimeEdit *edit = static_cast<QTimeEdit*>(editor);
    edit->setTime(time);
}

void TimeEditDeligate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *edit = static_cast<QTimeEdit*>(editor);
    QTime time = edit->time();
    model->setData(index,QVariant(time.toString("hh:mm")));
}

void TimeEditDeligate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

///*************************************************************/
//TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
// {
//     parentItem = parent;
//     itemData = data;
// }
//TreeItem::~TreeItem()
// {
//     qDeleteAll(childItems);
// }
//TreeItem *TreeItem::parent()
// {
//     return parentItem;
// }
//TreeItem *TreeItem::child(int number)
// {
//     return childItems.value(number);
// }
//int TreeItem::childCount() const
// {
//     return childItems.count();
// }
//int TreeItem::childNumber() const
// {
//     if (parentItem)
//         return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

//     return 0;
// }
//int TreeItem::columnCount() const
// {
//     return itemData.count();
// }
//QVariant TreeItem::data(int column) const
// {
//     return itemData.value(column);
// }
//bool TreeItem::setData(int column, const QVariant &value)
// {
//     if (column < 0 || column >= itemData.size())
//         return false;

//     itemData[column] = value;
//     return true;
// }
//bool TreeItem::insertChildren(int position, int count, int columns)
// {
//     if (position < 0 || position > childItems.size())
//         return false;

//     for (int row = 0; row < count; ++row) {
//         QVector<QVariant> data(columns);
//         TreeItem *item = new TreeItem(data, this);
//         childItems.insert(position, item);
//     }

//     return true;
// }
//bool TreeItem::removeChildren(int position, int count)
// {
//     if (position < 0 || position + count > childItems.size())
//         return false;

//     for (int row = 0; row < count; ++row)
//         delete childItems.takeAt(position);

//     return true;
// }
//bool TreeItem::insertColumns(int position, int columns)
//{
//    if (position < 0 || position > itemData.size())
//        return false;

//    for (int column = 0; column < columns; ++column)
//        itemData.insert(position, QVariant());

//    foreach (TreeItem *child, childItems)
//        child->insertColumns(position, columns);

//    return true;
//}
///***********************************************************/
//TreeModel::TreeModel(const QStringList &headers, const QString &data,
//                      QObject *parent)
//     : QAbstractItemModel(parent)
// {
//     QVector<QVariant> rootData;
//     foreach (QString header, headers)
//         rootData << header;

//     rootItem = new TreeItem(rootData);
//     setupModelData(data.split(QString("\n")), rootItem);
// }
//TreeModel::~TreeModel()
// {
//     delete rootItem;
// }
//TreeItem *TreeModel::getItem(const QModelIndex &index) const
// {
//     if (index.isValid()) {
//         TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
//         if (item) return item;
//     }
//     return rootItem;
// }
//int TreeModel::rowCount(const QModelIndex &parent) const
// {
//     TreeItem *parentItem = getItem(parent);

//     return parentItem->childCount();
// }
//int TreeModel::columnCount(const QModelIndex & /* parent */) const
// {
//     return rootItem->columnCount();
// }
//Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return 0;

//     return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
// }
//QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
// {
//     if (parent.isValid() && parent.column() != 0)
//         return QModelIndex();
//     TreeItem *parentItem = getItem(parent);

//      TreeItem *childItem = parentItem->child(row);
//      if (childItem)
//          return createIndex(row, column, childItem);
//      else
//          return QModelIndex();
//  }
//QModelIndex TreeModel::parent(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return QModelIndex();

//     TreeItem *childItem = getItem(index);
//     TreeItem *parentItem = childItem->parent();

//     if (parentItem == rootItem)
//         return QModelIndex();

//     return createIndex(parentItem->childNumber(), 0, parentItem);
// }
//----------------------------------------------------------------------
CheckGroup::CheckGroup(QStringList labelStrs, QWidget *parent)
    : QGroupBox(parent)
{
    setAutoFillBackground(true);
    QRgb rgb = qRgb(120, 120, 120);
    QPalette p1;
    p1 = palette();
    p1.setColor(QPalette::Window,rgb);
    setPalette(p1);

    QGridLayout *glay = new QGridLayout;
    for(int i=0; i<labelStrs.size(); i++)
    {
        QCheckBox *tmpCheckBox = new QCheckBox(labelStrs[i]);
        m_CheckBoxList.append(tmpCheckBox);
        glay->addWidget(tmpCheckBox, i/2, i%2, 1, 1);
        connect(m_CheckBoxList[i], SIGNAL(clicked()), this, SLOT(updateCheckBoxes()));
    }
    setLayout(glay);
}

CheckGroup::CheckGroup(QWidget *parent)
    : QGroupBox(parent)
{
    setAutoFillBackground(true);
    QRgb rgb = qRgb(120, 120, 120);
    QPalette p1;
    p1 = palette();
    p1.setColor(QPalette::Window,rgb);
    setPalette(p1);
//    this->setFixedHeight(20);
}

void CheckGroup::setCheckBoxWithTitles(QStringList strTitleList)
{
    foreach(QCheckBox *checkBox, m_CheckBoxList)
        checkBox->setChecked(false);

    foreach(QString str, strTitleList)
    {
        foreach(QCheckBox *checkBox, m_CheckBoxList)
        {
            if(checkBox->text() == str)
                checkBox->setChecked(true);
        }
    }
}

void CheckGroup::updateCheckBoxes(void)
{
    m_CheckedTitleList.clear();
    foreach(QCheckBox *checkBox, m_CheckBoxList)
    {
        if(checkBox->isChecked())
            m_CheckedTitleList.append(checkBox->text());
    }
}

void CheckGroup::setCheckBoxes(QStringList labelStrs)
{
    QGridLayout *glay = new QGridLayout;
    for(int i=0; i<labelStrs.size(); i++)
    {
        QCheckBox *tmpCheckBox = new QCheckBox(labelStrs[i]);
        m_CheckBoxList.append(tmpCheckBox);
        glay->addWidget(tmpCheckBox, i/1, i%1, 1, 1);
        connect(m_CheckBoxList[i], SIGNAL(clicked()), this, SLOT(updateCheckBoxes()));
    }
    setLayout(glay);
}

CheckGroupDeligate::CheckGroupDeligate(QStringList labelStrs, QObject *parent)
     :QItemDelegate(parent)
{
    foreach(QString lb, labelStrs)
        m_TitleStringList.append(lb);
}


QWidget *CheckGroupDeligate::createEditor(QWidget *parent, const QStyleOptionViewItem &,const QModelIndex &) const
{
    CheckGroup *editor = new CheckGroup(parent);
    editor->setCheckBoxes(m_TitleStringList);
    editor->installEventFilter(const_cast <CheckGroupDeligate*> (this));
    editor->setCheckBoxWithTitles(m_TitleStringList);
    return editor;
}

void CheckGroupDeligate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString editStr = index.model()->data(index).toString();
    QStringList strlst = editStr.split(";");
    CheckGroup *edit = static_cast <CheckGroup*> (editor);
    edit->setCheckBoxWithTitles(strlst);
    edit->updateCheckBoxes();
}

void CheckGroupDeligate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CheckGroup *edit = static_cast <CheckGroup*> (editor);
    QString str;
    foreach(QString tmpstr, edit->m_CheckedTitleList)
    {
        str.append(tmpstr);
        str.append(";");
    }
    model->setData(index, QVariant(str));
}

void CheckGroupDeligate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    QRect rect;
    rect.setX(option.rect.x());
    rect.setY(option.rect.y());
    rect.setWidth(option.rect.width());
    rect.setHeight(m_TitleStringList.size()*22);
    editor->setGeometry(rect);
}
