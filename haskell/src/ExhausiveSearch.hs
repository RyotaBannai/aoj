module ExhausiveSearch where

import Common (readInputsTerm)
import Data.Foldable (toList)

run :: [Int] -> Int -> Int -> Bool
run xs n m = go xs m
  where
    go (x : xs) m
      | m == 0 = True
      | m < 0 = False
      | otherwise = go xs m || go xs (m - x)
    go [] m = m == 0

readInts :: IO [Int]
readInts = map read . words <$> getLine

main :: IO ()
main = do
  n <- read <$> getLine
  xs <- readInts
  _ <- getLine
  ys <- readInts
  mapM_ putStrLn . toList $ map (conv . run xs n) ys
  where
    conv b = if b then "yes" else "no"