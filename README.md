# QtModule

自研 Qt 模块集合，提供可直接集成到 Qt 项目的可复用控件。

---

## 模块列表

| 模块 | 版本 | 说明 |
|---|---|---|
| [LoggerWidget](#loggerwidget) | 1.0.0 | 异步日志查看控件，支持实时写入与历史查询 |
| [HistoryCalendarDialog](#historycalendardialog) | 1.0.0 | 历史日历模态对话框控件，用于以日历形式展示具有历史记录的日期集供用户选择 |

---

## LoggerWidget

基于 Qt 的异步日志查看控件，包含 **实时日志** 与 **历史查询** 两个功能页签。

### 核心特性

- 将结构化日志以 CSV 格式异步追加写入本地文件，不阻塞 UI 主线程
- 分页展示日志，支持向上/向下翻页，LRU 缓存加速读取
- 自定义每条记录的显示格式，空字段自动跳过
- 通过回调函数自定义每行的字体颜色、背景色和字体（绕过 QSS/原生主题）
- 写入后自动切换到最新页，同页追加无闪屏
- **历史查询**：按日期 + 时间区间 + 关键词模糊匹配检索，支持前一个/后一个高亮导航
- 内置日历对话框（`HistoryCalendarDialog`）：仅展示有日志记录的日期，防止无效选择
- 每天零点自动清理超过 6 个月的旧日志

### 环境要求

| 要求 | 版本 |
|---|---|
| Qt | 5.x / 6.x |
| C++ 标准 | C++17 |
| Qt 模块 | `core` `gui` `widgets` |

### 目录结构

```
LoggerWidget/
├── LoggerWidget_V_1_0_0.pro     # 演示工程入口
├── main.cpp                     # 演示程序入口
├── mainwindow.h/.cpp/.ui        # 演示主窗口
└── loggerwidget/                # 模块源码
    ├── loggerwidget.pri          # 模块 pri 文件（集成入口）
    ├── loggerwidget.h/.cpp/.ui   # 主控件（UI 层）
    ├── logicalfilesystem.h/.cpp  # 逻辑代理层（主线程）
    ├── logfilesystem.h/.cpp      # 文件系统层（Worker Thread）
    ├── logpagemodel.h/.cpp       # 数据模型层
    ├── logitemdelegate.h/.cpp    # 自定义绘制委托
    ├── loadmoreitemwidget.h/.cpp # 翻页按钮控件
    ├── csvio.h/.cpp              # CSV 读写工具
    ├── itemstyle.h               # 行样式描述结构体（纯头文件）
    ├── historyquery.h            # 历史查询参数/结果结构体（纯头文件）
    ├── lrucache.h                # LRU 缓存模板类（纯头文件）
    ├── pagetable.h               # 页表相关结构体（纯头文件）
    └── historycalendardialog/    # 日历日期选择对话框子模块
        ├── historycalendardialog.pri
        ├── historycalendardialog.h/.cpp/.ui
        └── HistoryCalendarDialog_Design.md
```

### 架构分层

```
┌──────────────────────────────────────────────┐
│              LoggerWidget                    │  ← UI 层（QWidget，含实时/历史双 Tab）
│   ┌──────────────┐  ┌────────────────────┐   │
│   │ LogPageModel │  │ LogItemDelegate    │   │  ← 模型层 + 绘制委托
│   └──────────────┘  └────────────────────┘   │
│   ┌──────────────┐  ┌────────────────────┐   │
│   │ ItemStyle    │  │ LoadMoreItemWidget │   │  ← 样式描述 + 翻页按钮
│   └──────────────┘  └────────────────────┘   │
├──────────────────────────────────────────────┤
│           LogicalFileSystem                  │  ← 逻辑代理层（主线程）
├──────────────────────────────────────────────┤
│      LogFileSystem（Worker Thread）          │  ← 文件系统层（独立线程，LRU 缓存）
├──────────────────────────────────────────────┤
│               CsvIO                          │  ← I/O 工具层（CSV 读写）
└──────────────────────────────────────────────┘
```

所有文件 I/O 均在独立 Worker Thread 中执行（`QThread::moveToThread`），主线程与工作线程间通过信号槽（`QueuedConnection`）通信，**无需互斥锁**。

日志文件存储路径：`<rootPath>/yyyyMM/dd_HHmmss.csv`，同一天内复用同一文件。

### 快速集成

**1. 将模块 pri 引入工程（`.pro` 文件）：**

```qmake
include($$PWD/loggerwidget/loggerwidget.pri)
INCLUDEPATH += $$PWD/loggerwidget
```

**2. 在 `.ui` 文件中添加 `QWidget` 并 Promote 为 `LoggerWidget`（头文件路径：`loggerwidget.h`）。**

**3. 在代码中配置并初始化：**

```cpp
#include "loggerwidget.h"
#include "itemstyle.h"

// 配置顺序：setHeaders → setFormat → setItemStyler → setPageSize → initialize
QString logRoot = QCoreApplication::applicationDirPath() + "/logs";
ui->loggerWidget->setRootPath(logRoot);

ui->loggerWidget->setHeaders({
    "level", "时间", "qrcode", "警报id", "是否解决", "解决时间", "具体信息"
});

// 格式中 {} 按顺序对应 args，值为空时自动跳过该段
ui->loggerWidget->setFormat(
    "[{}][{}][{}][{}][{}][{}]:{}",
    {"level", "时间", "qrcode", "警报id", "是否解决", "解决时间", "具体信息"}
);

// 可选：按字段设置行样式（绕过 QSS）
ui->loggerWidget->setItemStyler([](const QStringList &record, ItemStyle &style) {
    const QString &level = record.value(0);
    if (level == "error") {
        style.setForeground(QColor(255, 80,  80));
        style.setBackground(QColor(60,  10,  10));
    } else if (level == "warn") {
        style.setForeground(QColor(255, 165,  0));
        style.setBackground(QColor(50,  35,   0));
    }
});

ui->loggerWidget->setPageSize(100);
ui->loggerWidget->initialize();   // 最后调用，触发异步加载

// 连接写入结果信号
connect(ui->loggerWidget, &LoggerWidget::logWritten, this, [](bool ok) {
    if (!ok) qWarning() << "日志写入失败";
});
```

**4. 写入日志：**

```cpp
QJsonObject record;
record["level"]    = "info";
record["时间"]     = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
record["qrcode"]   = "QR-000001";
record["警报id"]   = "ALT-0001";
record["是否解决"] = "否";
record["解决时间"] = "";       // 空字段在显示时自动跳过
record["具体信息"] = "设备离线";

ui->loggerWidget->writeLog(record);
```

### 注意事项

- `setHeaders` 必须在 `initialize` 之前调用
- `setFormat` 的 `args` 中的表头名须与 `setHeaders` 中的字符串完全一致
- `initialize` 只需调用一次；此后每次 `writeLog` 成功均自动刷新到写入页
- 控件内部线程在析构时自动 `quit()` + `wait()`，无需手动管理

### 详细设计文档

- 实时日志模块：[`loggerwidget/design.md`](LoggerWidget/loggerwidget/design.md)
- 日历对话框：[`loggerwidget/historycalendardialog/HistoryCalendarDialog_Design.md`](LoggerWidget/loggerwidget/historycalendardialog/HistoryCalendarDialog_Design.md)

---

## HistoryCalendarDialog

基于 Qt 的 **历史日历模态对话框** 控件。用于以日历形式展示具有历史记录的日期集供用户选择。

### 核心特性

- **仅显示具有历史记录的年月**：年月下拉框仅列出具有数据的选项
- **视觉区分**：具有历史记录的日期以黑色字体显示，空白日期以浅灰色显示
- **选择保护**：用户无法选择空白日期
- **信号通知**：用户确认选择后，选中的日期通过信号发出

### 环境要求

| 要求 | 版本 |
|---|---|
| Qt | 5.x / 6.x |
| C++ 标准 | C++17 |
| Qt 模块 | `core` `gui` `widgets` |

### 目录结构

```
Calendar/
|-- Calendar_V_1_0_0/           # 演示工程
|   |-- Calendar_V_1_0_0.pro    # 演示工程入口
|   |-- main.cpp                # 演示程序入口
|   |-- mainwindow.h/.cpp/.ui   # 演示主窗口
|   |-- HistoryCalendarDialog_Design.md  # 设计文档
|   |-- historycalendardialog/  # 模块源码
|   |   |-- historycalendardialog.pri     # 模块 pri 文件
|   |   |-- historycalendardialog.h/.cpp/.ui  # 主控件
|   |   -- HistoryCalendarDialog_Design.md  # 设计文档
```

### UI 布局

```
+-------------------------------------------------+
|  labelTitle ("选择日期")                      |  <- QLabel，12pt 字体
+-------------------------------------------------+
|  comboYear    comboMonth    [stretch]           |  <- QHBoxLayout，间距 20
+-------------------------------------------------+
|                                                 |
|            calendarWidget                       |  <- QCalendarWidget，最小高度 280
|                                                 |
+-------------------------------------------------+
|           [stretch]   btnCancel  btnConfirm     |  <- QHBoxLayout，右对齐
+-------------------------------------------------+
```

### 快速集成

**1. 将模块 pri 引入工程（`.pro` 文件）：**

```qmake
include($$PWD/historycalendardialog/historycalendardialog.pri)
INCLUDEPATH += $$PWD/historycalendardialog
```

**2. 在代码中使用：**

```cpp
#include "historycalendardialog.h"

// 创建对话框实例
HistoryCalendarDialog dialog(this);

// 设置可用日期（例如，具有日志记录的日期）
QSet<QDate> availableDates;
availableDates.insert(QDate(2024, 1, 15));
availableDates.insert(QDate(2024, 1, 20));
dialog.setAvailableDates(availableDates);

// 显示模态对话框
if (dialog.exec() == QDialog::Accepted) {
    QDate selected = dialog.selectedDate();
    qDebug() << "用户选择的日期：" << selected.toString("yyyy-MM-dd");
}

// 或连接信号用于异步使用
connect(&dialog, &HistoryCalendarDialog::dateSelected, 
        this, [](const QDate &date) {
            qDebug() << "日期选择：" << date;
        });
```

### 公开接口

| 方法 | 描述 |
|---|---|
| `setAvailableDates(const QSet<QDate> &dates)` | 设置可用日期集 |
| `selectedDate() const` | 获取当前选中的日期 |
| `setSelectedDate(const QDate &date)` | 设置当前选中的日期 |
| 信号 `dateSelected(const QDate &date)` | 用户确认选择后发出 |

### 注意事项

- 对话框默认以模态方式运行
- 年月下拉框仅显示具有可用日期的选项
- 空白日期以浅灰色显示，无法被选择
- 可用日期变化时自动更新日历格式

### 详细设计文档

- 日历对话框：[`Calendar/Calendar_V_1_0_0/HistoryCalendarDialog_Design.md`](Calendar/Calendar_V_1_0_0/HistoryCalendarDialog_Design.md)
