// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2020 The Dash Core developers
// Copyright (c) 2020-2022 The Raptoreum developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include <config/crystal-bitoreum-config.h>
#endif

#include <qt/splashscreen.h>

#include <qt/guiutil.h>
#include <qt/networkstyle.h>

#include <chainparams.h>
#include <clientversion.h>
#include <init.h>
#include <interfaces/handler.h>
#include <interfaces/node.h>
#include <interfaces/wallet.h>
#include <util.h>
#include <ui_interface.h>
#include <version.h>

#include <QApplication>
#include <QCloseEvent>
#include <QDate>
#include <QDesktopWidget>
#include <QFontMetrics>
#include <QKeyEvent>
#include <QLinearGradient>
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QSize>
#include <QtGlobal>

static QString CopyrightYears()
{
    const int startYear = 2025;
    const int currentYear = QDate::currentDate().year();

    if (currentYear > startYear) {
        return QString("%1-%2").arg(startYear).arg(currentYear);
    }

    return QString::number(startYear);
}

static void DrawSplashTextFades(QPainter& painter, int width, int height)
{
    // Dark purple/navy preserves the neon artwork better than pure black.
    const QColor fadeColor(10, 8, 32);

    const int topFadeHeight = static_cast<int>(height * 0.24);
    QLinearGradient topFade(0, 0, 0, topFadeHeight);
    topFade.setColorAt(0.00, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 185));
    topFade.setColorAt(0.45, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 95));
    topFade.setColorAt(1.00, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 0));
    painter.fillRect(QRect(0, 0, width, topFadeHeight), topFade);

    const int bottomFadeHeight = static_cast<int>(height * 0.26);
    QLinearGradient bottomFade(0, height, 0, height - bottomFadeHeight);
    bottomFade.setColorAt(0.00, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 170));
    bottomFade.setColorAt(0.50, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 85));
    bottomFade.setColorAt(1.00, QColor(fadeColor.red(), fadeColor.green(), fadeColor.blue(), 0));
    painter.fillRect(QRect(0, height - bottomFadeHeight, width, bottomFadeHeight), bottomFade);
}

static void DrawSplashBranding(QPainter& painter, int width, int height, float fontFactor)
{
    const QColor accentColor(0, 255, 213);      // Website teal.
    const QColor textColor(235, 245, 255);      // Soft white.
    const QColor panelColor(7, 10, 26);         // Deep navy.
    const QColor panelEdgeColor(0, 255, 213, 35);

    const QString networkText = QObject::tr("Bitoreum Network");
    const QString copyrightText = QString::fromUtf8("© %1 The Crystal Bitoreum developers")
                                      .arg(CopyrightYears());
    const QString hostedText = QObject::tr("Hosted by Ramen Wukong");

    // Lower-center readability pocket for network branding.
    const int panelWidth = static_cast<int>(width * 0.78);
    const int panelHeight = static_cast<int>(height * 0.18);
    const int panelX = (width - panelWidth) / 2;
    const int panelY = static_cast<int>(height * 0.69);

    QRect panelRect(panelX, panelY, panelWidth, panelHeight);

    QPainterPath panelPath;
    panelPath.addRoundedRect(panelRect, 8, 8);

    QLinearGradient panelGradient(0, panelRect.top(), 0, panelRect.bottom());
    panelGradient.setColorAt(0.00, QColor(panelColor.red(), panelColor.green(), panelColor.blue(), 65));
    panelGradient.setColorAt(0.35, QColor(panelColor.red(), panelColor.green(), panelColor.blue(), 150));
    panelGradient.setColorAt(1.00, QColor(panelColor.red(), panelColor.green(), panelColor.blue(), 95));

    painter.fillPath(panelPath, panelGradient);

    painter.setPen(panelEdgeColor);
    painter.drawPath(panelPath);

    QFont titleFont = GUIUtil::getFontBold();
    titleFont.setPointSize(static_cast<int>(24 * fontFactor));
    titleFont.setCapitalization(QFont::AllUppercase);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 3.5);
    painter.setFont(titleFont);
    painter.setPen(accentColor);

    QFontMetrics titleMetrics(painter.fontMetrics());
    const int titleY = panelRect.top() + static_cast<int>(panelHeight * 0.36);
    painter.drawText((width - titleMetrics.width(networkText)) / 2, titleY, networkText);

    QFont smallFont = GUIUtil::getFontNormal();
    smallFont.setPointSize(static_cast<int>(11 * fontFactor));
    smallFont.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);
    painter.setFont(smallFont);
    painter.setPen(textColor);

    QFontMetrics smallMetrics(painter.fontMetrics());

    const int copyrightY = panelRect.top() + static_cast<int>(panelHeight * 0.63);
    painter.drawText((width - smallMetrics.width(copyrightText)) / 2, copyrightY, copyrightText);

    const int hostedY = panelRect.top() + static_cast<int>(panelHeight * 0.83);
    painter.drawText((width - smallMetrics.width(hostedText)) / 2, hostedY, hostedText);
}

SplashScreen::SplashScreen(interfaces::Node& node, Qt::WindowFlags f, const NetworkStyle *networkStyle) :
    QWidget(0, f), curAlignment(0), m_node(node)
{

    // transparent background
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");

    // no window decorations
    setWindowFlags(Qt::FramelessWindowHint);

    // Geometries of splashscreen
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);

    int width = qMax(320, qMin(480, int(screenGeometry.width() * 0.55)));
    int height = qMax(360, qMin(540, int(screenGeometry.height() * 0.72)));
    int logoWidth = width;
    int logoHeight = height;

    // set reference point, paddings
    int paddingTop = 5;
    int titleVersionVSpace = 20;

    float fontFactor = qMax(0.70f, qMin(1.0f, width / 480.0f));
    float scale = qApp->devicePixelRatio();

    // define text to place
    QString titleText    = tr("Bitoreum Network");
    QString versionText  = QString::fromStdString(FormatFullVersion());
    QString titleAddText = networkStyle->getTitleAddText();

    QFont fontNormal = GUIUtil::getFontNormal();
    QFont fontBold   = GUIUtil::getFontBold();

    QPixmap pixmapLogo = networkStyle->getSplashImage();
    pixmapLogo.setDevicePixelRatio(scale);

    // TODO: Do we want to shade the splash screen for testnet/devnet?
    // Adjust logo color based on the current theme
    // QImage imgLogo = pixmapLogo.toImage().convertToFormat(QImage::Format_ARGB32);
    // QColor logoColor = GUIUtil::getThemedQColor(GUIUtil::ThemedColor::BLUE);
    // for (int x = 0; x < imgLogo.width(); ++x) {
    //     for (int y = 0; y < imgLogo.height(); ++y) {
    //         const QRgb rgb = imgLogo.pixel(x, y);
    //         imgLogo.setPixel(x, y, qRgba(logoColor.red(), logoColor.green(), logoColor.blue(), qAlpha(rgb)));
    //     }
    // }
    // pixmapLogo.convertFromImage(imgLogo);

    pixmap = QPixmap(width * scale, height * scale);
    pixmap.setDevicePixelRatio(scale);
    pixmap.fill(GUIUtil::getThemedQColor(GUIUtil::ThemedColor::BORDER_WIDGET));

    QPainter pixPaint(&pixmap);
    pixPaint.setRenderHint(QPainter::Antialiasing, true);
    pixPaint.setRenderHint(QPainter::TextAntialiasing, true);
    pixPaint.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QRect rect = QRect(1, 1, width - 2, height - 2);
    pixPaint.fillRect(rect, GUIUtil::getThemedQColor(GUIUtil::ThemedColor::BACKGROUND_WIDGET));

    pixPaint.drawPixmap((width / 2) - (logoWidth / 2),
                        (height / 2) - (logoHeight / 2),
                        pixmapLogo.scaled(logoWidth * scale,
                                          logoHeight * scale,
                                          Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation));

    // check font size and drawing with
    fontBold.setPointSize(50 * fontFactor);
    pixPaint.setFont(fontBold);
    QFontMetrics fm = pixPaint.fontMetrics();
    int titleTextWidth = fm.width(titleText);
    if (titleTextWidth > width * 0.8) {
        fontFactor = qMin(fontFactor, 0.75f);
    }

    DrawSplashTextFades(pixPaint, width, height);
    DrawSplashBranding(pixPaint, width, height, fontFactor);

    //pixPaint.setPen(GUIUtil::getThemedQColor(GUIUtil::ThemedColor::DEFAULT));
    pixPaint.setPen(Qt::white);

    fontNormal.setPointSize(static_cast<int>(18 * fontFactor));
    fontNormal.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);
    pixPaint.setFont(fontNormal);
    fm = pixPaint.fontMetrics();

    int versionTextWidth = fm.width(versionText);
    pixPaint.drawText((width / 2) - (versionTextWidth / 2),
                      titleVersionVSpace + fm.ascent(),
                      versionText);

    // draw additional text if special network
    if (!titleAddText.isEmpty()) {
        fontBold.setPointSize(24 * fontFactor);
        pixPaint.setFont(fontBold);
        fm = pixPaint.fontMetrics();
        int titleAddTextWidth = fm.width(titleAddText);
        // Draw the badge backround with the network-specific color
        QRect badgeRect = QRect(0, 0, titleAddTextWidth + 10, fm.height() + 10);
        QColor badgeColor = networkStyle->getBadgeColor();
        pixPaint.fillRect(badgeRect, badgeColor);
        // Draw the text itself using white color, regardless of the current theme
        pixPaint.setPen(Qt::white);
        pixPaint.drawText(5, fm.height(), titleAddText);
    }

    pixPaint.end();

    // Resize window and move to center of desktop, disallow resizing
    QRect r(QPoint(), QSize(width, height));
    resize(r.size());
    setFixedSize(r.size());
    move(screenGeometry.center() - r.center());

    subscribeToCoreSignals();
    installEventFilter(this);
}

SplashScreen::~SplashScreen()
{
    unsubscribeFromCoreSignals();
}

bool SplashScreen::eventFilter(QObject * obj, QEvent * ev) {
    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        if (!keyEvent->text().isEmpty() && keyEvent->text()[0] == 'q') {
            m_node.startShutdown();
        }
    }
    return QObject::eventFilter(obj, ev);
}

void SplashScreen::slotFinish(QWidget *mainWin)
{
    Q_UNUSED(mainWin);

    /* If the window is minimized, hide() will be ignored. */
    /* Make sure we de-minimize the splashscreen window before hiding */
    if (isMinimized())
        showNormal();
    hide();
    deleteLater(); // No more need for this
}

static void InitMessage(SplashScreen *splash, const std::string &message)
{
    QMetaObject::invokeMethod(splash, "showMessage",
        Qt::QueuedConnection,
        Q_ARG(QString, QString::fromStdString(message)),
        Q_ARG(int, Qt::AlignBottom | Qt::AlignHCenter),
        Q_ARG(QColor, Qt::white));
//      Q_ARG(QColor, GUIUtil::getThemedQColor(GUIUtil::ThemedColor::DEFAULT)));
}

static void ShowProgress(SplashScreen *splash, const std::string &title, int nProgress, bool resume_possible)
{
    InitMessage(splash, title + std::string("\n") +
            (resume_possible ? _("q = quit, resumes later")
                                : _("q = quit")) +
            strprintf("\n%d", nProgress) + "%");
}
#ifdef ENABLE_WALLET
void SplashScreen::ConnectWallet(std::unique_ptr<interfaces::Wallet> wallet)
{
    m_connected_wallet_handlers.emplace_back(wallet->handleShowProgress(boost::bind(ShowProgress, this, _1, _2, false)));
    m_connected_wallets.emplace_back(std::move(wallet));
}
#endif

void SplashScreen::subscribeToCoreSignals()
{
    // Connect signals to client
    m_handler_init_message = m_node.handleInitMessage(boost::bind(InitMessage, this, _1));
    m_handler_show_progress = m_node.handleShowProgress(boost::bind(ShowProgress, this, _1, _2, _3));
#ifdef ENABLE_WALLET
    m_handler_load_wallet = m_node.handleLoadWallet([this](std::unique_ptr<interfaces::Wallet> wallet) { ConnectWallet(std::move(wallet)); });
#endif
}

void SplashScreen::unsubscribeFromCoreSignals()
{
    // Disconnect signals from client
    m_handler_init_message->disconnect();
    m_handler_show_progress->disconnect();
#ifdef ENABLE_WALLET
    m_handler_load_wallet->disconnect();
#endif // ENABLE_WALLET
    for (auto& handler : m_connected_wallet_handlers) {
        handler->disconnect();
    }
    m_connected_wallet_handlers.clear();
    m_connected_wallets.clear();
}

void SplashScreen::showMessage(const QString &message, int alignment, const QColor &color)
{
    curMessage = message;
    curAlignment = alignment;
    curColor = color;
    update();
}

void SplashScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QFont messageFont = GUIUtil::getFontNormal();
    messageFont.setStyleStrategy(QFont::PreferAntialias);
    messageFont.setPointSize(11);
    messageFont.setLetterSpacing(QFont::AbsoluteSpacing, 0.4);
    painter.setFont(messageFont);
    painter.drawPixmap(0, 0, pixmap);
    QRect r = rect().adjusted(3, 5, -3, -18);
    painter.setPen(curColor);
    painter.drawText(r, curAlignment, curMessage);
}

void SplashScreen::closeEvent(QCloseEvent *event)
{
    m_node.startShutdown(); // allows an "emergency" shutdown during startup
    event->ignore();
}
