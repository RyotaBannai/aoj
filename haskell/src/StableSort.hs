{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module StableSort where

import Common (swapElems)
import Control.Monad (liftM2)
import Data.List
import Data.Maybe

-- * ALDS1_2_C

data Card = Card {suit :: Char, value :: Int}

-- Card {suit = a, value = b} == Card {suit = c, value = d} = a == c
instance Eq Card where
  c1 == c2 = value c1 == value c2

instance Ord Card where
  c1 `compare` c2 = value c1 `compare` value c2

instance Show Card where
  show c = suit c : (show . value $ c)

ssort :: [Card] -> [Card]
ssort [] = []
ssort xs = y : zs
  where
    y : ys = ssort' xs
    zs = ssort ys

ssort' :: [Card] -> [Card]
ssort' [x] = [x]
ssort' xs =
  let i = fromJust (elemIndex (minimum xs) xs)
   in if i == 0 then xs else swapElems 0 i xs

bsort :: [Card] -> [Card]
bsort [] = []
bsort xs = y : zs
  where
    y : ys = bsort' xs
    zs = bsort ys

bsort' :: [Card] -> [Card]
bsort' [x] = [x]
bsort' (x : xs)
  | y < x = y : x : ys -- be cautious! do not to do `<=`
  | otherwise = x : y : ys
  where
    y : ys = bsort' xs

toCard :: String -> Card
toCard s = Card {suit = head s, value = (read :: String -> Int) . tail $ s}

toStr :: [Card] -> [String]
toStr = map show

run :: String -> [String]
run s = liftM2 format ssort bsort $ map toCard . words $ s

format :: [Card] -> [Card] -> [String]
format s b =
  let s' = toStr s
      b' = toStr b
   in [unwords b', "Stable", unwords s', conv . isStable $ (b', s')]
  where
    conv b = if b then "Stable" else "Not stable"

isStable :: ([String], [String]) -> Bool
isStable t = all (uncurry (==)) $ uncurry zip t

main :: IO ()
main = getLine >> getLine >>= mapM_ putStrLn . run