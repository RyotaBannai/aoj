module MSort where

halve :: [a] -> ([a], [a])
halve [] = ([], [])
halve xs = let mid = (`div` 2) . length $ xs in splitAt mid xs

-- 1. singleton list どうしの比較であれば確実にソート + マージ可能
-- 2. ソート済みの 2 つのリストであればマージ + ソート可能
-- merge [1,6,2] [9,5,1] # [1,6,2,9,5,1]

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x : xs) (y : ys)
  | x < y = x : merge xs (y : ys)
  | otherwise = y : merge (x : xs) ys

msort :: Ord a => [a] -> [a]
msort [] = []
msort [x] = [x]
msort xs = let (left, right) = halve xs in merge (msort left) (msort right)

readInts :: IO [Int]
readInts = map read . words <$> getLine

format :: ([Int], Int) -> [String]
format (xs, cnt) = [unwords . map show $ xs, show cnt]

main :: IO ()
main = do
  _ <- getLine
  xs <- readInts
  mapM_ putStrLn $ format . msort xs
