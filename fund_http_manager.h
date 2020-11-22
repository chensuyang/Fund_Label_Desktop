#ifndef FUND_HTTP_MANAGER_H
#define FUND_HTTP_MANAGER_H
#include <QObject>
#include <QNetworkReply>
typedef struct
{
    QString fund_code;              // 基金代码
    QString fund_name;              // 基金名称
    double fund_net_worth;          // 基金单位净值
    double fund_expect_worth;       // 基金净值估算
    double fund_expect_growth;      // 基金净单位净值估算日涨幅
    QString fund_net_worth_date;    // 基金净值更新日期
    QString fund_expect_worth_date; // 基金净值估算更新日期

}fund_info_struct;

class Fund_HTTP_Manager : public QObject
{
    Q_OBJECT
public:

    static Fund_HTTP_Manager *getInstance();

signals:

    // 查询净值信息
    void Signal_QueryFundInfoReply(fund_info_struct* fund_info);

public slots:
    // 查询净值信息回复
    void Slot_QueryFundInfo(QString fund_code[],int fund_number);

private slots:
    // 查询净值信息HTTP接口回复
    void Slot_QueryFundInfoReplyFinished(void);

private:
    explicit Fund_HTTP_Manager(QObject *parent = 0);
    static Fund_HTTP_Manager* instance;
    QNetworkReply *query_fund_info_reply;

};

#endif // FUND_HTTP_MANAGER_H


