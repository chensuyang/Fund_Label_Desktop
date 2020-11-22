import QtQuick 2.12
import QtQuick.Window 2.12
import Toou2D 1.0
import "."

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("苏阳基金查看器v1.0")
    Column{
        x: 30
        y: 20
        id:layout
        spacing: 10
        Fund_info_box{
            id: fund_info_box_1
            fund_name:"基金1"
        }
        Fund_info_box{
            id: fund_info_box_2
            fund_name:"基金2"
        }
        Fund_info_box{
            id: fund_info_box_3
            fund_name:"基金3"
        }
        Fund_info_box{
            id: fund_info_box_4
            fund_name:"基金4"
        }
        Fund_info_box{
            id: fund_info_box_5
            fund_name:"基金5"
        }

    }
}
