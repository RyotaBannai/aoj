{-# LANGUAGE ViewPatterns #-}

module Partition where

import Control.Monad (liftM2)
import Data.Foldable (toList)
import Data.Vector (Vector)
import qualified Data.Vector as V

run :: Vector Int -> Int -> (Vector Int, Vector Int, Int)
run xs base = let (smaller, bigger) = swap xs base (V.empty, V.empty) in (smaller, bigger, base)

swap :: Vector Int -> Int -> (Vector Int, Vector Int) -> (Vector Int, Vector Int)
swap (uncons -> Nothing) base st = st
swap (uncons -> Just (x, xs)) base (smaller, bigger) =
  if x <= base
    then swap xs base (V.snoc smaller x, adjust bigger)
    else swap xs base (smaller, V.snoc bigger x)

uncons :: Vector Int -> Maybe (Int, Vector Int)
uncons as
  | V.null as = Nothing
  | otherwise = Just (V.head as, snd $ V.splitAt 1 as)

adjust :: Vector Int -> Vector Int
adjust b = case uncons b of
  Nothing -> b
  Just (x, xs) -> V.snoc xs x

format :: (Vector Int, Vector Int, Int) -> String
format (smaller, adjust -> bigger, base) = unwords . toList $ V.concat [format' smaller, V.fromList ["[" ++ show base ++ "]"], format' bigger]

format' :: Vector Int -> Vector String
format' = V.map show

main :: IO ()
main = (getLine >> getLine) >>= putStrLn . format . uncurry run . liftM2 (,) (V.fromList . init) last . map read . words
