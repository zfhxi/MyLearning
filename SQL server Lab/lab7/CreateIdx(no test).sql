USE Library

-- Create Clustered Index For Reader
CREATE CLUSTERED INDEX clu_idx ON Reader (Rno ASC) WITH (DROP_EXISTING = ON)

-- Create unique Index For Book
CREATE UNIQUE INDEX uniclu_idx ON Book (Bno ASC) WITH (DROP_EXISTING = ON)

-- Create NonClustered Index For Borrow
CREATE NONCLUSTERED INDEX nonclu_idx ON Borrow (Rno ASC, BorrowDate DESC) WITH (DROP_EXISTING = ON)