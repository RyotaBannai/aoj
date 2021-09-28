{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module BSearch where

import Data.Vector (Vector, (!))
import qualified Data.Vector as V

type S = Vector Int

type Right = Int

type Left = Int

type Target = Int

search :: S -> Left -> Right -> Target -> Int
search s l r t
  | (r - l) <= 1 = 0
  | s ! m == t = 1
  | s ! m > t = search s l m t
  | s ! m < t = search s m r t
  where
    m = (l + r) `div` 2

readInt :: IO Int
readInt = read <$> getLine

readInts :: IO (Vector Int)
readInts = V.fromList . map read . words <$> getLine

main :: IO ()
main = (\n s t -> V.map (search s 0 n) t) <$> readInt <*> readInts <*> (getLine >> readInts) >>= print . V.sum
