{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Algo where

import Common (randomList, readInputContest, readInputsTerm, safeSwapElems)
import Control.Applicative
import Data.List
import Data.Maybe
import System.IO

-- ITP1_1_C: Rectangle
solve :: IO ()
solve = do
  [a, b] <- map read . words <$> getLine
  let area = a * b
      rect = a + 2 + b + 2
  print $ show area ++ " " ++ show rect

-- ALDS1_1_D
solve2 :: IO ()
solve2 = do
  _ <- getLine
  xs <- fmap read <$> readInputsTerm -- or use `readInputsTerm` for debug
  print $ run xs Nothing Nothing
  where
    prof :: Integer -> Integer -> Integer
    prof f s
      | s < 0 && f > 0 = f + s
      | otherwise = (-) s f

    run :: [Integer] -> Maybe Integer -> Maybe Integer -> Integer
    run [] (Just x) _ = x
    run (v : rest) maxv Nothing = run rest maxv (Just v)
    run (v : rest) Nothing (Just x) = run rest (Just $ prof x v) (Just (x `min` v))
    run (v : rest) (Just v') (Just x) = run rest (Just $ prof x v `max` v') (Just (x `min` v))

bubbleSort :: Ord a => [a] -> (Int, [a])
bubbleSort = outer 0 0
  where
    outer :: (Ord a) => Int -> Int -> [a] -> (Int, [a])
    outer i time xs =
      let (times', flag', xs') = inner i (length xs - 1) time False xs
       in if not flag' then (times', xs') else outer (i + 1) times' xs'

    inner :: (Ord a) => Int -> Int -> Int -> Bool -> [a] -> (Int, Bool, [a])
    inner i j times flag xs
      | j <= i = (times, flag, xs)
      | (xs !! j) < (xs !! (j -1)) =
        let xs' = fromJust $ safeSwapElems j (j -1) xs
         in inner i (j -1) (times + 1) True xs'
      | otherwise = inner i (j -1) times flag xs

-- test :: IO ()
-- test = do
--   xs <- randomList 100
--   let (time, xs') = bubbleSort xs
--   putStrLn $ "times: " ++ show time ++ ", sorted list: " ++ show xs'

solve3 :: IO ()
solve3 = do
  _ <- getLine
  xs <- map read . words <$> getLine
  let (time, xs') = bubbleSort xs :: (Int, [Int])
  putStrLn $ unwords . map show $ xs'
  print time

{-
napo's ans | <https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2411742#1>

just sort with default impl
and the number of sort is calculated just by finding minimun elem index and sum those indices.

-}
solve3' :: IO ()
solve3' = getContents >>= putStr . format . (\xs -> (solve' ([], xs), sort xs)) . map read . words . (!! 1) . lines

format :: (([Int], [a]), [Int]) -> String
format ((ns, _), xs) = unlines [unwords $map show xs, show $ sum ns]

solve' :: ([Int], [Int]) -> ([Int], [Int])
solve' (n, []) = (n, [])
solve' (n, xs) = let s = minimum xs in solve' (fromJust (elemIndex s xs) : n, delete s xs)