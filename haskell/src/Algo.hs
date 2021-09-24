{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Algo where

import Common (readInputsTerm)
import Control.Applicative
import System.IO

-- ITP1_1_C: Rectangle
solve3 :: IO ()
solve3 = do
  [a, b] <- map read . words <$> getLine
  let area = a * b
      rect = a + 2 + b + 2
  print $ show area ++ " " ++ show rect

-- ALDS1_1_D
solve4 :: IO ()
solve4 = do
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
