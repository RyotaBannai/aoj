module Algo where

import Control.Applicative
import System.IO

-- ITP1_1_C: Rectangle
solve3 :: IO ()
solve3 = do
  [a, b] <- map read . words <$> getLine
  let area = a * b
      rect = a + 2 + b + 2
  print $ show area ++ " " ++ show rect

takeWhileM :: (Monad m, Functor m) => (a -> Bool) -> [m a] -> m [a]
takeWhileM p (ma : mas) = do
  a <- ma
  if p a
    then (a :) <$> takeWhileM p mas
    else return []
takeWhileM _ _ = return []

{-
takeWhileM <https://stackoverflow.com/questions/12119420/haskell-ghci-using-eof-character-on-stdin-with-getcontents>
-}

-- ALDS1_1_D
readInputContest :: IO [String]
readInputContest = lines <$> getContents

readInputsTerm :: IO [String]
readInputsTerm = takeWhileM (not . null) (repeat getLine)

solve4 :: IO ()
solve4 = do
  _ <- getLine
  xs <- fmap read <$> readInputsTerm -- or use `readInputsTerm` for debug
  print $ run xs Nothing Nothing
  where
    prof :: Integer -> Integer -> Integer
    prof f s
      | s < 0 = f + s
      | otherwise = (-) s f
    maxp v Nothing = v
    maxp v (Just v') = v `max` v'
    run :: [Integer] -> Maybe Integer -> Maybe Integer -> Integer
    run [] (Just x) _ = x
    run (v : rest) maxv minv = case minv of
      Nothing -> run rest maxv (Just v)
      Just x -> run rest (Just $ maxp (prof x v) maxv) (Just (x `min` v))

{-
solve4' :: IO ()
solve4' = do
  _ <- getLine
  xs <- fmap read <$> takeWhileM (not . null) (repeat getLine)
  print (maximum $ plist xs)
  where
    prof f s
      | s < 0 = f + s
      | otherwise = (-) s f
    plist :: [Integer] -> [Integer]
    plist [f] = []
    plist (f : s : rest) = prof f s : plist (s : rest)
-}