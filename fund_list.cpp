#include "fund_list.h"

Data::Data(void)
{
    fund_name_= "NULL";
    fund_code_ = 0;
    fund_net_worth_ = 0.0;
    fund_expect_worth_ = 0.0;
    fund_expect_growth_ = 0.0;
    fund_net_worth_date_ = "NULL";
    fund_expect_worth_date_ = "NULL";
}

Data::Data(const QString &fund_name,int fund_code,double fund_net_worth,double fund_expect_worth,double fund_expect_growth,const QString &fund_net_worth_date,const QString &fund_expect_worth_date)
{
    fund_name_= fund_name;
    fund_code_ = fund_code;
    fund_net_worth_ = fund_net_worth;
    fund_expect_worth_ = fund_expect_worth;
    fund_expect_growth_ = fund_expect_growth;
    fund_net_worth_date_ = fund_net_worth_date;
    fund_expect_worth_date_ = fund_expect_worth_date;
}

QString Data::fund_name() const
{
    return fund_name_;
}
int Data::fund_code() const
{
    return fund_code_;
}

double Data::fund_net_worth() const
{
    return fund_net_worth_;
}

double Data::fund_expect_worth() const
{
    return fund_expect_worth_;
}

double Data::fund_expect_growth() const
{
    return fund_expect_growth_;
}

QString Data::fund_net_worth_date() const
{
    return fund_net_worth_date_;
}


QString Data::fund_expect_worth_date() const
{
    return fund_expect_worth_date_;
}


DataModel::DataModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

DataModel::~DataModel()
{
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataList_.count();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= dataList_.count())
    {
        return QVariant();
    }
    const Data &data = dataList_[row];
    switch (role)
    {
    case FundNameRole:
        return data.fund_name();
    case FundCodeRole:
        return data.fund_code();
    case FundNetWorthRole:
        return data.fund_net_worth();
    case FundExpectWorthRole:
        return data.fund_expect_worth();
    case FundExpectGrowthRole:
        return data.fund_expect_growth();
    case FundNetWorthDateRole:
        return data.fund_net_worth_date();
    case FundExpectWorthDateRole:
        return data.fund_expect_worth_date();

    }

    return QVariant();
}


//dm : data model
QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FundNameRole] = "fundName";
    roles[FundCodeRole] = "fundCode";
    roles[FundNetWorthRole] = "fundNetWorth";
    roles[FundExpectWorthRole] = "fundExpectWorth";
    roles[FundExpectGrowthRole] = "fundExpectGrowth";
    roles[FundNetWorthDateRole] = "fundNet_worthDate";
    roles[FundExpectWorthDateRole] = "fundExpectWorthDate";

    return roles;
    //    emit countChanged(m_data.count());
}

void DataModel::insert(int index, const Data &data)
{
    if(index < 0 || index > dataList_.count()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    dataList_.insert(index, data);
    emit endInsertRows();
//    emit countChanged(m_data.count());
}

void DataModel::remove(int index)
{
    if(index < 0 || index >= dataList_.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    dataList_.removeAt(index);
    endRemoveRows();
}


void DataModel::append(const QString &fund_name,int fund_code,double fund_net_worth,double fund_expect_worth,double fund_expect_growth,const QString &fund_net_worth_date,const QString &fund_expect_worth_date)
{
    insert(count(), Data(fund_name,fund_code,fund_net_worth,fund_expect_worth,fund_expect_growth,fund_net_worth_date,fund_expect_worth_date));
}


int DataModel::count() const
{
    return rowCount(QModelIndex());
}
