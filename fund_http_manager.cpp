#include "fund_http_manager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QCryptographicHash>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Fund_HTTP_Manager *Fund_HTTP_Manager::instance = 0;

/*******************************************************************************
* Function Name  :  getInstance
* Description    :  获取单例
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
Fund_HTTP_Manager *Fund_HTTP_Manager::getInstance()
{
    if(instance == 0)
    {
        instance = new Fund_HTTP_Manager();
    }
    return instance;
}


/*******************************************************************************
* Function Name  :  Fund_HTTP_Manager
* Description    :  构造函数
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
Fund_HTTP_Manager::Fund_HTTP_Manager(QObject *parent):QObject(parent)
{

}

/*******************************************************************************
* Function Name  :  Slot_QueryFundInfo
* Description    :  查询基金信息
* Input          :  QString fund_code[]
* Input          :  int fund_number
* Output         :  None
* Return         :  None
*******************************************************************************/
void Fund_HTTP_Manager::Slot_QueryFundInfo(QString fund_code[],int fund_number)
{
    QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
    //设置url
    QString fund_code_arg = "";
    for(int i=0;i<fund_number;i++)
    {
        if(i==fund_number-1)
        {
            fund_code_arg=fund_code_arg+fund_code[i];
        }
        else
        {
            fund_code_arg=fund_code_arg+fund_code[i]+",";
        }
    }
    QString url = "https://api.doctorxiong.club/v1/fund?code="+fund_code_arg;
    QNetworkRequest requestInfo;
    requestInfo.setUrl(QUrl(url));

    query_fund_info_reply = m_pHttpMgr->get(requestInfo);
    qDebug() <<"获取网页内容";
    connect(query_fund_info_reply, SIGNAL(finished()), this, SLOT(Slot_QueryFundInfoReplyFinished()));
    if(query_fund_info_reply->isFinished())
    {
        qDebug() <<"获取网页内容结束";
    }
    else
    {
        qDebug() <<"获取网页内容未结束";
    }
}

void Fund_HTTP_Manager::Slot_QueryFundInfoReplyFinished(void)
{
    qDebug() << "触发回调";
    //错误处理
    if (query_fund_info_reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "request protobufHttp NoError";
    }
    else
    {
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = query_fund_info_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        // statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
    }
    // 请求返回的结果
    QTextCodec *codec = QTextCodec::codecForName("utf8");

    QByteArray query_fund_info_reply_byte_array = query_fund_info_reply->readAll();
    QString str = codec->toUnicode(query_fund_info_reply_byte_array);
    qDebug() << query_fund_info_reply_byte_array;
    qDebug() << str;
    // 释放replay对象
    query_fund_info_reply->deleteLater();

    QJsonParseError jsonError;

    // 转为json
    QJsonDocument doucment = QJsonDocument::fromJson(query_fund_info_reply_byte_array, &jsonError);

        // 解析未发生错误
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            // JSON 文档为对象
            if (doucment.isObject())
            {
                // 转化为对象
                QJsonObject root_object = doucment.object();

                // 包含指定的 key
                if (root_object.contains("data"))
                {
                    QJsonValue value = root_object.value("data");

                    if(value.isArray())
                    {
                        QJsonArray fund_info_array = value.toArray();

                        fund_info_struct* tmp_fund_info_struct = new fund_info_struct[fund_info_array.count()];

                        // 遍历所有基金
                        for(int i=0;i<fund_info_array.count();i++)
                        {
                            if (fund_info_array[i].isObject())
                            {
                                // root_object 的 data 是对象
                                QJsonObject data_object = fund_info_array[i].toObject();

                                // 包含指定的 key 基金代码
                                if (data_object.contains("code"))
                                {
                                    QJsonValue value = data_object.value("code");
                                    if (value.isString())
                                    {
                                        tmp_fund_info_struct[i].fund_code = value.toString();
                                    }
                                }
                                // 包含指定的 key 基金名称
                                if (data_object.contains("name"))
                                {
                                    QJsonValue value = data_object.value("name");
                                    if (value.isString())
                                    {
                                        tmp_fund_info_struct[i].fund_name = value.toString();
                                    }
                                }
                                // 包含指定的 key 基金净值更新日期
                                if (data_object.contains("netWorthDate"))
                                {
                                    QJsonValue value = data_object.value("netWorthDate");
                                    if (value.isString())
                                    {
                                        tmp_fund_info_struct[i].fund_net_worth_date = value.toString();
                                    }
                                }
                                // 包含指定的 key 基金单位净值
                                if (data_object.contains("netWorth"))
                                {
                                    QJsonValue value = data_object.value("netWorth");
                                    if (value.isDouble())
                                    {
                                        tmp_fund_info_struct[i].fund_net_worth = value.toDouble();
                                    }
                                }
                                // 包含指定的 key 基金净单位净值估算日涨幅
                                if (data_object.contains("expectWorth"))
                                {
                                    QJsonValue value = data_object.value("expectWorth");
                                    if (value.isDouble())
                                    {
                                        tmp_fund_info_struct[i].fund_expect_growth = value.toDouble();
                                    }
                                }

                                qDebug() << "基金"<<i<<"代码:" <<tmp_fund_info_struct[i].fund_code;
                                qDebug() << "基金"<<i<<"名称:" <<tmp_fund_info_struct[i].fund_name;
                                qDebug() << "基金"<<i<<"净值更新日期:" <<tmp_fund_info_struct[i].fund_net_worth_date;
                                qDebug() << "基金"<<i<<"单位净值:" <<tmp_fund_info_struct[i].fund_net_worth;
                                qDebug() << "基金"<<i<<"净单位净值估算日涨幅:" <<tmp_fund_info_struct[i].fund_expect_growth;
                            }
                            else
                            {
                                qDebug() << "json error2";
                            }
                        }
                    }
                }
                else
                {
                    qDebug() << "json error1";
                }
            }
            else
            {
                qDebug() << "is not json obj1";
            }
        }
        else
        {
            qDebug() << "json decode fail:";
        }


}


