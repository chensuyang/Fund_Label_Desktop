import QtQuick 2.12
import QtQuick.Window 2.12
import Toou2D 1.0
import "."

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("苏阳基金查看器v1.0")


    ListView{
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        width: 600
        height: 400
        id:listView
        spacing: 10
        model:$Model
        delegate:delegate1
    }


    Component {
           id: delegate1
           Fund_info_box
           {
               fund_code:fundCode// 基金代码
               fund_name:fundName// 基金名称
               //fund_net_worth:fundNetWorth// 基金单位净值
               fund_expect_worth:"净值估算:"+fundExpectWorth// 基金净值估算
               fund_expect_growth:"净值估算日涨幅:"+fundExpectGrowth+"%"// 基金净单位净值估算日涨幅
               //fund_net_worth_date:fundNetWorthDate// 基金净值更新日期
               //fund_expect_worth_date:fundExpectWorthDate// 基金净值估算更新日期
               anchors.right: parent.right
               anchors.left: parent.left
               onRemove_fund_info_box:{
                console.log("Fund_Code:"+fundCode)
               }
           }
    }
}
