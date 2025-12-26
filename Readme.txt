============================================================
                  FOOD ORDERING SYSTEM
============================================================
Name : Robinjeet Singh
FILES OVERVIEW
------------------------------------------------------------
header.h      - Struct definitions, constants, and declarations
header.cpp    - Core program logic (menu loading, ordering,
                calculations, receipt saving)
driver.cpp    - Main entry point (program flow & payments)
Menu.txt      - Menu items in format: id,name;price&quantity
receipt.txt   - Auto-created/appended with each receipt

------------------------------------------------------------
HOW TO COMPILE & RUN
------------------------------------------------------------
1. Place all files in the same folder.
2. Open terminal / PowerShell in that folder.
3. Run:

   Must run this first : g++ header.cpp driver.cpp -o food_ordering
   			 ./food_ordering

Error : If Cant find "Menu.txt". Make sure Menu.txt is in same file 
	or change line '10' in driver.cpp (to your Menu.txt folder)

------------------------------------------------------------
📋 HOW TO USE
------------------------------------------------------------
1. The program loads Menu.txt and displays the menu.
2. For each new customer:
   - Enter Menu IDs and quantities to order.
   - Enter 0 to finish the order.

3. Item Selection:
   - Invalid IDs (>20) will prompt again.
   - Out of stock items will show a (out of stock)message and will be skip.
   - Non-numeric input (abc, etc) is cleared and re-prompted.

4. Quantity:
   - If you order more than available, it asks again.
   - If all stock is taken by previous customers, the program
     will show "out of stock" to new customers

5. Payment:
   - Choose 1 (Cash), 2 (Card), or 3 (eWallet).
   - Invalid payment choices re-prompt until valid.
   - Cash: if amount < total, it re-prompts until enough is given.

6. Receipt:
   - receipt.txt is created automatically if not found.
   - If it exists, new receipts are added without removing or overwriting data.

7. Order IDs:
   - Start at 59 and increase for each order.
   - Reset every program run to mimic real restaurants where
     order IDs reset daily.

------------------------------------------------------------
ERROR HANDLING & FEATURES
------------------------------------------------------------
- File existence check (Menu.txt)
- Invalid / non-numeric menu ID handling
- Out of stock detection
- Quantity validation and re-prompt
- Multiple order lines per customer
- Unique incremental order IDs
- Auto receipt file creation
- Formatted aligned receipts
- Payment input validation and re-prompt loops
- Cash payments validated against total
- Persistent receipts across program runs

------------------------------------------------------------
MENU FILE FORMAT
------------------------------------------------------------
Each line in Menu.txt should look like:
   1,Chicken Burger;7.50&10

Where:
   1    = Menu ID
   Chicken Burger = Item Name
   7.50 = Price
   10   = Quantity available

------------------------------------------------------------
EXAMPLE RECEIPT OUTPUT
------------------------------------------------------------
Order ID: 59 | Table: 1
--------------------------------------------------------------
ID   Item                       Quantity     Price        Line
1    Chicken Burger                   2       7.50       15.00
2    French Fries                     1       3.00        3.00
--------------------------------------------------------------
Total : RM 18.00
Payment Method: Cash
Change: RM 2.00

------------------------------------------------------------
End of README
