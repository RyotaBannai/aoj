{-# LANGUAGE TupleSections #-}

module MSort where

merge :: Ord a => ([a], [a], Int) -> ([a], Int)
merge (xs, [], cnt) = (xs, cnt + 1)
merge ([], ys, cnt) = (ys, cnt + 1)
merge (x : xs, y : ys, cnt)
  | x < y = (x : merged1, cnt1' + 1)
  | otherwise = (y : merged2, cnt2' + 1)
  where
    (merged1, cnt1') = merge (xs, y : ys, cnt)
    (merged2, cnt2') = merge (x : xs, ys, cnt)

msort :: Ord a => ([a], Int) -> ([a], Int)
msort ([], cnt) = ([], cnt)
msort ([x], cnt) = ([x], cnt)
msort (xs, cnt) =
  let (left, right) = halve xs
      (ls, cnt1) = msort (left, 0)
      (rs, cnt2) = msort (right, 0)
   in merge (ls, rs, cnt + cnt1 + cnt2)

halve :: [a] -> ([a], [a])
halve [] = ([], [])
halve xs = let mid = (`div` 2) . length $ xs in splitAt mid xs

readInts :: IO [Int]
readInts = map read . words <$> getLine

format :: ([Int], Int) -> [String]
format (xs, cnt) = [unwords . map show $ xs, show cnt]

main :: IO ()
main = (getLine >> readInts) >>= mapM_ putStrLn . format . msort . (,0)