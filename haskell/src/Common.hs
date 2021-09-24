module Common where

import System.Random

{-
takeWhileM <https://stackoverflow.com/questions/12119420/haskell-ghci-using-eof-character-on-stdin-with-getcontents>
-}

takeWhileM :: (Monad m, Functor m) => (a -> Bool) -> [m a] -> m [a]
takeWhileM p (ma : mas) = do
  a <- ma
  if p a
    then (a :) <$> takeWhileM p mas
    else return []
takeWhileM _ _ = return []

readInputContest :: IO [String]
readInputContest = lines <$> getContents

readInputsTerm :: IO [String]
readInputsTerm = takeWhileM (not . null) (repeat getLine)

-- λ safeSwapElems 1 9 [0..10] # Just [0,9,2,3,4,5,6,7,8,1,10]
safeSwapElems :: Int -> Int -> [a] -> Maybe [a]
safeSwapElems f' s' xs
  | f' == s' = Just xs
  | f' < 0 || s' < 0 || f' > length xs || s' > length xs = Nothing
  | otherwise =
    let (f, s) = if f' < s' then (f', s') else (s', f')
        elf = xs !! f
        els = xs !! s
        left = take f xs
        middle = take (s - f - 1) (drop (f + 1) xs)
        right = drop (s + 1) xs
     in Just $ left ++ els : middle ++ elf : right

randomList :: Int -> IO [Int]
randomList 0 = return []
randomList n = do
  r <- randomRIO (1, 6)
  rs <- randomList (n -1)
  return (r : rs)