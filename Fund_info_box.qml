import QtQuick 2.12
import Toou2D 1.0


TRectangle{
    id: tRectangle
    width: 600
    height: 60
    color: "#409EFF"
    radius: 2
    theme.enabled: false
    property alias fund_name : fund_name_tlabel.text                    // 对外暴露基金名称属性
    property alias fund_expect_worth : fund_expect_worth_tlabel.text    // 对外暴露基金净值估算属性
    property alias fund_expect_growth : fund_expect_growth_tlabel.text  // 对外暴露基金净单位净值估算日涨幅属性
    property alias fund_info_box_background_color : tRectangle.color    // 对外暴露基金信息框的背景颜色属性
    signal remove_fund_info_box()           // 定义点击删除按钮的信号

    TLabel{
        id: fund_name_tlabel                // 基金名标签
        x:10
        y:10
        width: 150
        height: 40
        color: "#FFF"
        text: "基金名"
        theme.enabled: false
    }
    TLabel{
        id: fund_expect_worth_tlabel        // 基金净值估算标签
        x:250
        y:10
        width: 150
        height: 40
        color: "#FFF"
        text: "净值估算:NULL"
        theme.enabled: false
    }
    TLabel{
        id: fund_expect_growth_tlabel        // 基金净单位净值估算日涨幅标签
        x:10
        y:35
        width: 150
        height: 40
        color: "#FFF"
        text: "净值估算日涨幅:NULL%"
        theme.enabled: false
    }
    TIconButton{
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        label.text: "删除"
        label.font.bold: true
        label.color: "#FFF"
        background.color: "#609EFF"
        icon.source: TAwesomeType.FA_close
        icon.color:label.color
        theme.enabled: false
        onClicked:
        {
            // 发射信号
            tRectangle.remove_fund_info_box()
        }
    }
}
