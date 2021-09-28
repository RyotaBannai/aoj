module ExhausiveSearch where

import Common (readInputsTerm)

run :: [Int] -> Int -> Bool
run (x : xs) m
  | m == 0 = True
  | m < 0 = False
  | otherwise = run xs m || run xs (m - x)
run [] m = m == 0

readInts :: IO [Int]
readInts = map read . words <$> getLine

main :: IO ()
main = do
  _ <- getLine
  xs <- readInts
  _ <- getLine
  ys <- readInts
  mapM_ (putStrLn . conv . run xs) ys
  where
    conv b = if b then "yes" else "no"