import numpy as np
import pandas as pd

random_values = np.round(np.random.rand(60), 4)
stock_price = 100.00
bank_balance = 1000.00
number_of_stock = 0
records = []

for month, u in enumerate(random_values, start=1):
    if u < 0.5:
        pass
    elif u < 0.75:
        stock_price *= 0.95
    else:
        stock_price *= 1.05

    if bank_balance > 0 and stock_price < 95:
        action = "Buy"
        number_of_stock = bank_balance / stock_price
        bank_balance = 0
    elif number_of_stock > 0 and stock_price > 110:
        action = "Sell"
        bank_balance += (number_of_stock * stock_price)
        number_of_stock = 0
    else:
        action = "None"
    interest_amount = (bank_balance * 0.0005)
    new_balance = bank_balance + interest_amount
    records.append([month, u, round(stock_price, 2), action, number_of_stock, round(stock_price * number_of_stock, 2),
                    round(bank_balance, 2), round(interest_amount, 2), round(new_balance, 2)])
    bank_balance = new_balance

df = pd.DataFrame(records, columns=["Month", "Random Value", "New Stock Price", "Action", "Number of Stock", "Worth"
    , "Bank Balance", "Interest Amount", "New Balance Amount"])
print(df)

df.to_csv("quiz5 simulation.csv", index=False)
