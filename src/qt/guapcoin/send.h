// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2019-2020 The Guapcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SEND_H
#define SEND_H

#include <QWidget>
#include <QPushButton>

#include "qt/guapcoin/pwidget.h"
#include "qt/guapcoin/contactsdropdown.h"
#include "qt/guapcoin/sendmultirow.h"
#include "qt/guapcoin/sendcustomfeedialog.h"
#include "walletmodel.h"
#include "coincontroldialog.h"
#include "qt/guapcoin/tooltipmenu.h"

static const int MAX_SEND_POPUP_ENTRIES = 8;

class GuapcoinGUI;
class ClientModel;
class WalletModel;
class WalletModelTransaction;

namespace Ui {
	class send;
	class QPushButton;
}

class SendWidget : public PWidget
{
	Q_OBJECT

public:
	explicit SendWidget(GuapcoinGUI* parent);
	~SendWidget();

	void addEntry();

	void loadClientModel() override;
	void loadWalletModel() override;

Q_SIGNALS:
	/** Signal raised when a URI was entered or dragged to the GUI */
	void receivedURI(const QString& uri);

	public Q_SLOTS:
	void onChangeAddressClicked();
	void onChangeCustomFeeClicked();
	void onCoinControlClicked();
	void onOpenUriClicked();
	void onValueChanged();
	void refreshAmounts();
	void changeTheme(bool isLightTheme, QString &theme) override;

protected:
	void resizeEvent(QResizeEvent *event) override;

	private Q_SLOTS:
	void onSendClicked();
	void onContactsClicked(SendMultiRow* entry);
	void onMenuClicked(SendMultiRow* entry);
	void onAddEntryClicked();
	void clearEntries();
	void clearAll();
	void refreshView();
	void onContactMultiClicked();
	void onDeleteClicked();
	void onResetCustomOptions(bool fRefreshAmounts);
private:
	Ui::send *ui;
	QPushButton *coinIcon;
	QPushButton *btnContacts;

	SendCustomFeeDialog* customFeeDialog = nullptr;
	bool isCustomFeeSelected = false;

	int nDisplayUnit;
	QList<SendMultiRow*> entries;
	CoinControlDialog *coinControlDialog = nullptr;

	ContactsDropdown *menuContacts = nullptr;
	TooltipMenu *menu = nullptr;
	// Current focus entry
	SendMultiRow* focusedEntry = nullptr;

	void resizeMenu();
	QString recipientsToString(QList<SendCoinsRecipient> recipients);
	SendMultiRow* createEntry();
	bool send(QList<SendCoinsRecipient> recipients);
	void updateEntryLabels(QList<SendCoinsRecipient> recipients);

};

#endif // SEND_H
