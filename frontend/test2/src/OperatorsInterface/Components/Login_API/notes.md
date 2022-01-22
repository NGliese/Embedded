Notes for logic api:

# should it be called "load_order"?

    - since we do not really log in, but rather load an order

//BUGFIXED
There is a bug in modal first element : we cannot use "OnClick" when the first element is the one we want to use

//TODO
Usecase load existing order in :

1. Scan / insert ordernumber.
   -Should we test if the chosen machine can make the order?
2. Change to OperatorPanel
   -- this should be a new link ( route )....

Usecase change machine : OK

1. click "Change Machine"
2. Modal opens with the ability to select a new machine
3. choose a new machine
4. set the current machine to the new chosen one

//TODO
Usecase create a new order
prereq : order number is not in db

1. click "Create"
2. Modal opens and displays:
   "order number"
