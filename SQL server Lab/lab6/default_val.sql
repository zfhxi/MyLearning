use Library
alter  table Borrow with CHECK
add constraint default_borrowdate default (GetDate()) for BorrowData