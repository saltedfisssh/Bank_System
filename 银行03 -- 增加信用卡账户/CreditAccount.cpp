#include "CreditAccount.h"

void CreditAccount::record(Date date, double amount, string desc)
{
	acc.getAccumulation(date);
	amount = floor(amount * 100 + 0.5) / 100;//保留小数点后两位
	setBalance(-amount);	// 更新余额
	acc.setValue(getBalance());	// 更新累计者本金
	total -= amount;
	date.show();
	cout << "\t#" << getId() << "\t" << -amount << "\t" << getBalance() << '\t' << desc << endl;
}

// 存款
void CreditAccount::deposit(Date date, double amount, string desc)
{
	acc.getAccumulation(date);
	amount = floor(amount * 100 + 0.5) / 100;//保留小数点后两位
	setBalance(amount);
	acc.setValue(getBalance());	// 更新累计者本金
	total += amount;
	date.show();
	cout << "\t#" << getId() << "\t" << amount << "\t" << getBalance() << '\t' << desc << endl;
}

// 取款
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	record(date, amount, desc);
}

// 结算
void CreditAccount::settle(Date date)
{
	double interest;
	//if ((date.getYear() > acc.getLastDate().getYear() ||/*如果更新的年份 > 最后一次的年份*/
	//	(date.getYear() == acc.getLastDate().getYear() && date.getMonth() > acc.getLastDate().getMonth()/*年份相同但月份更大*/)))
	//{
	//	// 年循环
	//	for (int i = acc.getLastDate().getYear(); i <= date.getYear(); i++)
	//	{
	//		// 月循环
	//		for (int j = acc.getLastDate().getMonth(); j <= date.getMonth(); j++)
	//		{
	//			// 如果余额 < 0
	//			if (balance < 0)
	//			{
	//				// 闰年
	//				if (Date::isLeapYear(date.getYear() - 1))
	//				{
	//					interest = acc.accumulate(Date(i, j, 1)) * getRate() / 366;	// 利息
	//				}
	//				// 平年
	//				else
	//				{
	//					interest = acc.accumulate(Date(i, j, 1)) * getRate() / 365;	// 利息
	//				}
	//				if (interest != 0)
	//				{
	//					record(date, interest);
	//				}
	//				acc.reset();
	//			}
	//			// 如果是元月
	//			if (j == 1)
	//			{
	//				settleFee(Date(i, j, 1));	// 支付年费
	//			}
	//		}
	//		
	//	}
	//}


	interest = acc.accumulate(date) * getRate();

	if (interest != 0)
	{
		record(date, -interest);
	}
	if (date.getMonth() == 1)	// 交年费
	{

		settleFee(date);
	}
	acc.reset();
}

// 计算年费
void CreditAccount::settleFee(Date date)
{
	balance -= fee;
	total -= fee;
	date.show();
	cout << "\t#" << getId() << '\t' << -fee << '\t' << balance << "\tannual fee" << endl;
}

// 格式化输出
void CreditAccount::show()
{
	double temp_credit;
	if (balance < 0)
	{
		temp_credit = credit + balance;
	}
	else
	{
		temp_credit = credit;
	}
	cout << getId() << "\tBalance: " << balance << "\tAvailable credit:" << temp_credit;
}