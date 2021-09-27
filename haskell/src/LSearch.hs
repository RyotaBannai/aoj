{-# LANGUAGE ViewPatterns #-}

module LSearch where

import qualified Data.Sequence as S

type S = S.Seq Int

type T = S.Seq Int

type Result = [Int]

run :: S -> T -> Result -> Result
run s (S.viewl -> S.EmptyL) re = re
run s (S.viewl -> v S.:< t) re = if search s v then run s t (v : re) else run s t re

search :: S -> Int -> Bool
search (S.viewl -> S.EmptyL) v = False
search (S.viewl -> t S.:< ts) v
  | t == v = True
  | t < v = search ts v
  | otherwise = False

readInts :: IO [Int]
readInts = map (read :: String -> Int) . words <$> getLine

main :: IO ()
main = do
  _ <- getLine
  s <- readInts
  _ <- getLine
  t <- readInts
  print . length $ run (S.sort . S.fromList $ s) (S.fromList t) []
