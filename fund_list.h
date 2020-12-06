#ifndef FUND_LIST_DATA_MODEL_H
#define FUND_LIST_DATA_MODEL_H


#include <QAbstractListModel>


class Data
{
public:
    Data(void);
    Data(const QString &fund_name,int fund_code,double fund_net_worth,double fund_expect_worth,double fund_expect_growth,const QString &fund_net_worth_date,const QString &fund_expect_worth_date);

    QString fund_name() const;
    int fund_code() const;
    double fund_net_worth() const;
    double fund_expect_worth() const;
    double fund_expect_growth() const;
    QString fund_net_worth_date() const;
    QString fund_expect_worth_date() const;

private:

    QString fund_name_;
    int fund_code_;
    double fund_net_worth_;
    double fund_expect_worth_;
    double fund_expect_growth_;
    QString fund_net_worth_date_;
    QString fund_expect_worth_date_;
};


class DataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles{
            FundNameRole = Qt::UserRole + 1,
            FundCodeRole,
            FundNetWorthRole,
            FundExpectWorthRole,
            FundExpectGrowthRole,
            FundNetWorthDateRole,
            FundExpectWorthDateRole
        };

    explicit DataModel(QObject *parent = nullptr);
       ~DataModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Add data:
        Q_INVOKABLE void insert(int index,const Data &data) ;

        // Remove data:
        Q_INVOKABLE void remove(int index);
        Q_INVOKABLE void append(const QString &fund_name,int fund_code,double fund_net_worth,double fund_expect_worth,double fund_expect_growth,const QString &fund_net_worth_date,const QString &fund_expect_worth_date);
        int count() const;

    protected: // interface QAbstractListModel
        virtual QHash<int, QByteArray> roleNames() const;

    private:
        QList<Data> dataList_;

};

#endif // FUND_LIST_DATA_MODEL_H
